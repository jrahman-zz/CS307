package org.rahmanj

import akka.actor._
import akka.event.Logging
import akka.io.IO

import scala.concurrent.Future
import scala.concurrent.duration._

import spray.http._

import spray.can.Http
import spray.routing.RequestContext
import HttpMethods._
import StatusCodes._


import com.github.mauricio.async.db.mysql.MySQLConnection
import com.github.mauricio.async.db.{Connection,Configuration}

import session._
import messages._

import tugboat._
import tugboat.Client
import tugboat.Build

import scala.concurrent.ExecutionContext.Implicits.global

case class InitializeSession(ctx: RequestContext, level: LevelSession)
case class SessionInitialized(ctx: RequestContext)
case class ContainerPing(success: Boolean)

class SessionActor(language: Any, hostname: String, port: Int) extends Actor with ActorLogging with Stash {
  
  implicit val system = ActorSystem()
  
  val tb = tugboat.Client()
  
  // Start in the initial state to receive a submission
  def receive: Receive = prepareInitialization
    
  def prepareInitialization: Receive = {
    case InitializeSession(ctx, levelSession) =>
      // TODO, start initialization
      val containerName = levelSession.language.containerName
      val containerPath = "/resources/containers/" + containerName 
      val containerStream = getClass.getResourceAsStream(containerPath)
      
      
      val newContainer = createContainer(/* TODO, params */)
      val levelInfo = loadLevelInformation(/* TODO, params*/)
      val finishedContainer = for {
        level <- levelInfo
        container <- newContainer
        finishedContainer <- initializeContainer(container, level)
  } yield finishedContainer
      
      // TODO, finishedContainer.map
      
    case _ => stash()
  }

  def finishInitialization: Receive = {
    case SessionInitialized(ctx) =>
      // TODO, finished initialization
    case _ => stash()
  }
    
  
  def receivePing: Receive = {
    case ContainerPing(result) =>
      result match {
        case true =>
          log.debug("Successful ping received")
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
    val hostname = this.hostname
    val port = this.port

    val interval = Settings(system).Container.PingInterval seconds
    implicit val timeout: Timeout = Timeout(interval)
    
    system.scheduler.scheduleOnce(interval) {
      val response = (IO(Http) ? HttpRequest(GET, getUri)).mapTo[HttpResponse] map {
        response => response.status match {
          case Success(_) => self ! ContainerPing(true)
          case _ => self ! ContainerPing(false)
        }
      } recover {
        case _ => self ! ContainerPing(false)
      }
    }
  }
  
  def getDatabaseConnection: Future[Connection] = {
    val configuration = Configuration(Settings(system).Database.Username)
    val connection = new MySQLConnection(configuration)
    connection.connect
  }
  
  def createContainer(): Future[Option[LevelSession]] = {
    // TODO
  }
  
  def initializeContainer() = {
    // TODO
  }
  
  def loadLevelInformation() = {
    // TODO
  }
      
  def getUri(): Uri = {
    Uri("http://" + hostname + ":" + port + "/ping")
  }
}
