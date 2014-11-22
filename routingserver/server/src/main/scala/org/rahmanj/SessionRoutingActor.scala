package org.rahmanj

import scala.util.Random

import akka.actor._
import spray.routing.RequestContext

import scala.collection.mutable.Map
import com.roundeights.hasher.Implicits._

import sessions._
import messages._
import routing._
import containers._

object SessionRoutingActor {
  
  /**
   * Create Props for an actor of this type
   * @param containerFactory Factory to create suitable container objects
   * @return A Props for creating this actor
   */
  def props(containerFactory: ContainerFactory): Props = Props(new SessionRoutingActor(containerFactory))
}

/** Actor that routes requests to the appropriate [[SessionActor]]
 * 
 * @constructor Creates a new instance of the [[SessionRoutingActor]]
 * @param containerFactory The [[org.rahmanj.container.ContainerFactory]] to create new instances
 */
class SessionRoutingActor(containerFactory: ContainerFactory) extends Actor with ActorLogging {

  implicit val system = ActorSystem()
  
  val router = new Router[ActorRef, RequestRoutable](token => sessionActor => msg => sessionActor ! msg.payload)
  
  /*
   * Track number of active containers
   */
  var containerCount = 0
  
  // Map LevelSession to LoginSession
  val sessionMap = Map[SessionToken, SessionToken]() 
  
  /*
   * Core switch to handle incoming msgs
   */
  def receive = {
    case msg: RequestRoutable =>
      sessionMap get msg.source match {
        case Some(session) if session == msg.context.login => 
          router.routeMessage(msg)
        case Some(session) => 
          msg.context.ctx.complete((403, "Not allowed to access that session"))
        case None => 
          msg.context.ctx.complete((404, "No such session exists"))
      }
    case CreateSession(ctx, loginSession, levelInfo) =>
      if (containerCount < Settings(system).Container.MaxContainers) {
        createSession(ctx, loginSession, levelInfo)
      } else {
        ctx.complete((503, "Too many sessions, come again later"))
      }
    case DeleteSession(ctx, loginSession, token) =>
      deleteSession(ctx, loginSession, token)
    case Terminated(sessionActor) =>
      terminateSession(sessionActor)
  }
  
  /*
   * 
   */
  def createSession(ctx: RequestContext, login: SessionToken, levelInfo: SessionCreateRequest) = {
    log.info("Creating new session")
    
    val token: SessionToken = (login.toString + Random.alphanumeric.take(20).mkString).sha512.hex
    
    val sessionActor = context.actorOf(SessionActor.props(containerFactory, token))
    
    /*
     * Register termination watcher
     */
    context.watch(sessionActor)
    
    // Update out state with the new route and session
    sessionMap += (token -> login)
    router.addRoute(token, sessionActor)
    
    // Send message to kick-start initialization proceedure
    log.info("Sending initialization message...")
    containerCount = containerCount + 1
    sessionActor ! InitializeSession(ctx, levelInfo, token)
  }
  
  /*
   * 
   */
  def deleteSession(ctx: RequestContext, loginSession: SessionToken, token: SessionToken) = {
    log.info("Deleting session")
    sessionMap get token match {
        case Some(session) if session == loginSession =>
          deleteSessionActor(token) match {
            case true => ctx.complete((200, "Deleted session"))
            case false => ctx.complete((500, "Failed to delete session"))
          }
        case Some(session) => ctx.complete((403, "Not allowed to access that session"))
        case None => ctx.complete((404, "No such session exists"))
      }
  }
  
  /*
   * Removes the route and deletes the session actor
   */
  def deleteSessionActor(token: SessionToken): Boolean = {
    
    log.info(s"Deleting session: $token")
    router.getRoute(token) match {
      case Some(actor) => context.stop(actor)
      case None => log.warning("No session found to delete")
    }
    router.removeRouteBySource(token)
  }
  
  /*
   * This is invoked when the underlying actor goes away
   */
  def terminateSession(sessionActor: ActorRef) = {
    log.info("Container terminated")
    containerCount = containerCount - 1
    router.removeRouteByDestination(sessionActor)
  }
}
