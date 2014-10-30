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
    case InitializeSession(ctx, req) =>
      
      log.info("Received initialization message, starting initialization procedure...")
      
      val futureContainer = createContainer(ContainerConfig())
      
      futureContainer.onComplete {
        case Success(container) =>
            sessionContainer = container
            sessionContainer match {
              case Some(container) =>
                log.info("Container initialized")
                
                schedulePing()
                context.become(receiveSubmission orElse receiveCommon)

                import spray.httpx.SprayJsonSupport._
                import messages.SessionCreateResponseProtocol._
                ctx.complete((200, container.sendMessage(req, "initialize")))
              case None =>
                log.info("Failed to crate container")
                ctx.complete((500, "Failed to create container"))
            }
        case Failure(throwable) =>
            log.error(throwable, "Failed to initialize container")
            ctx.complete((500, "Failed to create container"))
            // Indicate failure to the router
      }
    // Hideaway everything else until we are ready
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
    case _ => log.warning("Unknown message received by actor")
  }
  
  def receiveCommon = receivePing orElse receiveUnknown
  
  def receiveSubmission: Receive = {
    case Submission(ctx, submission) => sessionContainer match {
      case Some(container) => submission match {
        case levelSubmission: LevelSubmissionRequest =>
            
          log.info(s"Session $sessionID received level submission")
          import spray.httpx.SprayJsonSupport._
          import messages.LevelResultResponseProtocol._
          ctx.complete(container.sendMessage(levelSubmission, s"/level/submit/$sessionID"))
        case challengeSubmission: ChallengeSubmissionRequest =>
            
          log.info(s"Session $sessionID received challenge submission")
          import spray.httpx.SprayJsonSupport._
          import messages.ChallengeResultResponseProtocol._
          ctx.complete(container.sendMessage(challengeSubmission, s"/challenge/submit/$sessionID"))
      }
      case None => ctx.complete((500, "No session container available"))
    }
  }
  
  def schedulePing() {

    val interval = Settings(system).Container.PingInterval seconds
    implicit val timeout: Timeout = Timeout(interval)
    
    log.debug(s"Scheduling ping in $interval seconds")
    
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
}
