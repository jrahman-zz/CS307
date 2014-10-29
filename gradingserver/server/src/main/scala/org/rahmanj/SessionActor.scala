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

import sessions._
import messages._
import container._

import scala.concurrent.ExecutionContext.Implicits.global

case class InitializeSession(ctx: RequestContext, request: SessionCreateRequest)
case class SessionInitialized(ctx: RequestContext, container: Container)
// TODO, handle failed initialization

case class ContainerPing(success: Boolean)

object SessionActor {
  
  /**
   * Create Props for an actor of this type
   * @param containerFactory A factory to create suitable container objects
   * @return A Props for creating this actor
   */
  def props(containerFactory: ContainerFactory, sessionID: SessionToken): Props = Props(new SessionActor(containerFactory, sessionID))
}

/** An actor representing a level session
 * 
 * @constructor Create a session with the given factory object
 * @param containerFactory
 */
class SessionActor(containerFactory: ContainerFactory, sessionID: SessionToken) extends Actor with ActorLogging with Stash {
  
  implicit val system = ActorSystem()
  
  var sessionContainer: Option[Container] = None
  
  // Start in the initial state to receive an initialization 
  def receive: Receive = prepareInitialization
    
  def prepareInitialization: Receive = {
    case InitializeSession(ctx, levelInfo) =>
      
      log.info("Received initialization message, starting initialization procedure...")
      
      val futureContainer = createContainer(ContainerConfig())
      
      // This is a Monad!
      val finishedContainer = for {
        container <- futureContainer
        newContainer <- initializeContainer(container, levelInfo)
      } yield (newContainer match {
          case Some(container) => Future { Some(container) }
          case None => Future { None }
      })
      
      finishedContainer.onComplete {
        case Success(container) => 
            log.info("Container initialized")
            context.become(finishInitialization)
            self ! SessionInitialized
        case Failure(throwable) =>
            log.error(throwable, "Failed to initialize container")
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
      sessionContainer match {
        case Some(container) => submission match {
          case levelSubmission: LevelSubmissionRequest =>
            ctx.complete(container.sendMessage(levelSubmission, s"/level/submit/$sessionid"))
          case challengeSubmission: ChallengeSubmissionRequest =>
            ctx.complete(container.sendMessage(challengeSubmission, s"/challenge/submit/$sessionid"))
        case None => ctx.complete((500, "No session container available"))
      }
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
  
  def createContainer(config: ContainerConfig): Future[Option[Container]] = {
    containerFactory(ContainerConfig())
  }
  
  def initializeContainer(container: Option[Container], req: SessionCreateRequest): Future[Option[Container]] = {
    Future { container match {
        case Some(container) =>
          import spray.httpx.SprayJsonSupport._
          import messages.SessionCreateResponseProtocol._
          
          container.sendMessage(level, "/initialize")
          Some(container)
        case None => None
      }
    }
  }
}
