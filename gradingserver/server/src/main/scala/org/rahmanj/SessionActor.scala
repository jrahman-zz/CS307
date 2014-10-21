package org.rahmanj

import akka.actor._
import akka.event.Logging
import akka.pattern.Patterns.ask
import akka.io.IO
import akka.util.Timeout

import scala.util.{Success,Failure}
import scala.concurrent.Future
import scala.concurrent.duration._

import spray.http._

import spray.routing.RequestContext

import com.github.mauricio.async.db.mysql.MySQLConnection
import com.github.mauricio.async.db.{Connection,Configuration}

import sessions._
import messages._
import container._

import scala.concurrent.ExecutionContext.Implicits.global

case class InitializeSession(ctx: RequestContext, level: ClientCreateSession)
case class SessionInitialized(ctx: RequestContext, container: Container)
// TODO, handle failed initialization

case class ContainerPing(success: Boolean)

object SessionActor {
  
  /**
   * Create Props for an actor of this type
   * @param containerFactory A factory to create suitable container objects
   * @return A Props for creating this actor
   */
  def props(containerFactory: ContainerFactory): Props = Props(new SessionActor(containerFactory))
}

/** An actor representing a level session
 * 
 * @constructor Create a session with the given factory object
 * @param containerFactory
 */
class SessionActor(containerFactory: ContainerFactory) extends Actor with ActorLogging with Stash {
  
  implicit val system = ActorSystem()
  
  var sessionContainer: Option[Container] = None
  
  // Start in the initial state to receive an initialization 
  def receive: Receive = prepareInitialization
    
  def prepareInitialization: Receive = {
    case InitializeSession(ctx, levelInfo) =>
      val futureContainer = createContainer(ContainerConfig())
      val futureConnection = getDatabaseConnection
      
      // This is a Monad!
      val finishedContainer = for {
        connection <- futureConnection
        container <- futureContainer
        level <- loadLevelInformation(levelInfo, connection)
        newContainer <- initializeContainer(container, level)
      } yield (newContainer match {
          case Some(container) => Future { Some(container) }
          case None => Future { None }
      })
      
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
        case None => log.warning("Attempted to ping empty container")
      }
    }
  }
  
  def getDatabaseConnection: Future[Connection] = {
    val username = Settings(system).Database.Username
    val password = Settings(system).Database.Password
    val hostname = Settings(system).Database.Hostname
    val port     = Settings(system).Database.Port
    val configuration = Configuration(username, hostname, port, Some(password))
    val connection = new MySQLConnection(configuration)
    connection.connect
  }
  
  def createContainer(config: ContainerConfig): Future[Option[Container]] = {
    containerFactory(ContainerConfig())
  }
  
  def initializeContainer(container: Option[Container], level: ExecutorCreateSession): Future[Option[Container]] = {
    Future { container match {
        case Some(container) =>
          import spray.httpx.SprayJsonSupport._
          import messages.ExecutorSessionCreatedProtocol._
          
          container.sendMessage(level)
          Some(container)
        case None => None
      }
    }
  }
  
  def loadLevelInformation(level: ClientCreateSession, connection: Connection) = { 
    Future {
      ExecutorCreateSession(ExecutorLevel()) // TODO
    }
  }
}
