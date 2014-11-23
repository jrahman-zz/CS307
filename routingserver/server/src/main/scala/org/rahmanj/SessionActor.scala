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
import containers._

import spray.httpx.SprayJsonSupport._
import messages.SessionCreateResponseProtocol._

import scala.concurrent.ExecutionContext.Implicits.global

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
  
  // Start in the prepare initialization state
  def receive: Receive = prepareInitialization
  
  /**
   * Message receive handler for the initialization state
   * While in this state, we stash any messages other than the InitializeSession
   * message, and when we receive the InitializeSession message, we begin that
   * proceedure
   */
  def prepareInitialization: Receive = {
    case InitializeSession(ctx, req, token) =>
      
      log.info("Received initialization message, starting initialization procedure...")
      
      try {
        createContainer(DockerContainerConfig()).onComplete {
          case Success(container) =>
            initializeContainer(container, req, token)(ctx)
            schedulePing()
            context.become(receiveNormal orElse receiveCommon)
          case Failure(throwable) =>
              log.error(throwable, "Failed to initialize container")
              ctx.complete((500, "Failed to create container"))
              context.stop(self)
        }
      } catch {
        /*
         * Bailout here if anything bad happened
         */
        case ex: Throwable =>
          log.error(ex, "Failed to initialize container")
          ctx.complete((500, "Failed to create container"))
          context.stop(self)
      }
    // Hideaway everything else until we are ready, we will process later
    case _ => stash()
  }
  
  /*
   * Update actor state, and send initialize message to the container with level information
   */
  def initializeContainer[T <: Request](newContainer: Option[Container], req: SessionCreateRequest, token: SessionToken)(implicit ctx: RequestContext) = {
    newContainer match {
      case Some(container) =>
        log.info("Container created, initializing...")

        sessionContainer = newContainer
        import messages.SessionCreateResponseProtocol._
        ctx.complete((200, container.sendMessage(req, "initialize").map(res => SessionCreateResponse(true, token))))
      case None =>
        sessionContainer = None
        log.error("Failed to crate container")
        ctx.complete((500, "Failed to create container"))
        context.stop(self)
    }
  }
  
  /*
   * Process heartbeat pings from the container
   */
  def receivePing: Receive = {
    case ContainerPing(result) =>
      result match {
        case true =>
          log.debug("Successful ping returned")
          schedulePing
        case false =>
          // Crash and burn if our container has a problem
          log.error("Ping failed, terminating session...")
          context.stop(self)
      }
  }
  
  def receiveUnknown: Receive = {
    case _ => log.warning("Unknown message received by actor")
  }
  
  /*
   * Bundle these two together
   */
  def receiveCommon = receivePing orElse receiveUnknown
  
  def receiveSubmission: Receive = {
    case Submission(ctx, submission) => sessionContainer match {
      case Some(container) => forwardSubmission(ctx, container)(submission)
      case None => ctx.complete((500, "No session container available"))
    }
    
  }
  
  def receiveDeletion: Receive = {
    case DeleteSession(ctx, login, sesion) => sessionContainer match {
        case Some(container) => ctx.complete( {
              container.shutdown()
              "Deleted"
        })
        case None => ctx.complete((500, "No session container available"))
    }
  }
  
  /*
   * Bundle these two together
   */
  def receiveNormal = receiveSubmission orElse receiveDeletion

  /*
   * Blindly pass the message onto the container without inspection
   */
  def forwardSubmission(ctx: RequestContext, container: Container): PartialFunction[Request, Unit] = {
    {
      /*
       * Switch on each type of 
       */
    case levelSubmission: LevelSubmissionRequest =>
      log.info(s"Session $sessionID received level submission")

      import messages.LevelSubmissionRequestProtocol._
      import messages.LevelResultResponse._
      
      val res = container.sendMessage(levelSubmission, s"level/submit")
      res.onFailure {
        case result =>
          log.error(result, "Failed to contact the container")
          ctx.complete((500, "Unknown failure to contact the container"))
          context.stop(self)
      }
      res.onSuccess {
        case result => ctx.complete(result)
      }
    case challengeSubmission: ChallengeSubmissionRequest =>
      log.info(s"Session $sessionID received challenge submission")

      import messages.ChallengeSubmissionRequestProtocol._
      import messages.ChallengeResultResponse._
         
      val res = container.sendMessage(challengeSubmission, s"challenge/submit")
      res.onFailure {
        case result =>
          log.error(result, "Failed to contact the container")
          ctx.complete((500, "Unknown failure to contact the container"))
      }
      res.onSuccess {
        case result => ctx.complete(result)
      }
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
            case Success(result) => schedulePing() // Reset and start again
            case Failure(throwable) => {
              context.stop(self) // Die quickly
            }
          }
        case None => log.warning("Attempted to ping an empty container")
      }
    }
  }
  
  def createContainer(config: DockerContainerConfig): Future[Option[Container]] = {
    containerFactory(config)
  }

  /*
   * Terminate the container if safe to do so
   */
  def shutdownContainer() = {
    sessionContainer match {
      case Some(container) => container.shutdown()
    }
  }
  
  /*
   * Clean up the container as the actor is going away
   */
  override def postStop() {
    shutdownContainer()
  }
}
