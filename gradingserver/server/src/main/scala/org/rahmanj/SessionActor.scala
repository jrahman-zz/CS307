package org.rahmanj

import akka.actor._
import akka.event.Logging
import akka.pattern.Patterns.ask
import akka.io.IO

import scala.util.{Success,Failure}
import scala.concurrent.Future
import scala.concurrent.duration._

import spray.http._

import spray.routing.RequestContext

import com.github.mauricio.async.db.mysql.MySQLConnection
import com.github.mauricio.async.db.{Connection,Configuration}

import session._
import messages._
import container._

import scala.concurrent.ExecutionContext.Implicits.global

case class InitializeSession(ctx: RequestContext, level: ClientCreateSession)
case class SessionInitialized(ctx: RequestContext, container: Container)
case class ContainerPing(success: Boolean)

class SessionActor extends Actor with ActorLogging with Stash {
  
  implicit val system = ActorSystem()
  
  var sessionContainer: Option[Container] = None
  
  // Start in the initial state to receive an initialization 
  def receive: Receive = prepareInitialization
    
  def prepareInitialization: Receive = {
    case InitializeSession(ctx, levelInfo) =>
      val futureContainer = createContainer(ContainerConfig())
      val futureConnection = getDatabaseConnection()
      
      // This is a Monad!
      val finishedContainer = for {
        connection <- futureConnection
        container <- futureContainer
        level <- getLevelInfo(levelInfo, connection)
        newContainer <- initializeContainer(container, level)
      } yield newContainer
      
      finishedContainer.onComplete {
        case Success(container) => 
            self ! SessionInitialized
            context.become(finishInitialization)
        case Failure(throwable) =>
            // TODO, fail, fail hard and fast
      }
    // Hideaway, everything else until we are ready
    case _ => stash()
  }

  def finishInitialization: Receive = {
    case SessionInitialized(ctx, container) =>
      sessionContainer = Some(container)
      schedulePing()
      context.become(receiveSubmission orElse receiveCommon)
    case _ => stash()
  }
   
  def receivePing: Receive = {
    case ContainerPing(result) =>
      result match {
        case true =>
          log.debug("Successful ping returned")
          schedulePing
        case false =>
          log.debug("Ping failed")
          // TODO, scram, fail hard
      }
  }
  
  def receiveUnknown: Receive = {
    case _ => log.warning("Known message received by actor")
  }
  
  def receiveCommon = receivePing orElse receiveUnknown
  
//  def receiveResult: Receive = {
//    case ExecutorLevelResult(ctx, result) =>
//      // TODO
//      context.become(receiveSubmission orElse receiveCommon)
//    case ExecutorChallengeResult(ctx, result) =>
//      // TODO
//      context.become(receiveSubmission orElse receiveCommon)
//  }
  
  def receiveSubmission: Receive = {
    case Submission(ctx, submission) =>
      submission match {
        case levelSubmission: ClientLevelSubmission =>
          // TODO, pull level information
        case challengeSubmission: ClientChallengeSubmission =>
          // TODO, pull challenge information
      }
  }
  
  def schedulePing() {

    val interval = Settings(system).Container.PingInterval seconds
    implicit val timeout: Timeout = Timeout(interval)
    
    system.scheduler.scheduleOnce(interval) {
      sessionContainer match {
        case Some(container) =>
          container.ping.onComplete {
            case Success(result) => // TODO
            case Failure(throwable) => // TODO
          }
      }
    }
  }
  
  def getDatabaseConnection: Future[Connection] = {
    val configuration = Configuration(Settings(system).Database.Username) // TODO, add password, hostname, port, and database option
    val connection = new MySQLConnection(configuration)
    connection.connect
  }
  
  def createContainer(config: ContainerConfig): Future[Container] = {
    DummyContainer(ContainerConfig())
  }
  
  def initializeContainer(container: Container, level: ExecutorCreateSession) = {
    container.sendMessage(level)
  }
  
  def loadLevelInformation(level: ClientCreateSession, connection: Connection) = { 
    Future {
      "TODO"
    }
  }
}
