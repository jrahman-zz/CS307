package org.rahmanj

import scala.util.Random

import akka.actor._
import spray.routing.RequestContext

import scala.collection.mutable.Map
import com.roundeights.hasher.Implicits._

import sessions._
import messages._
import routing._
import container._


object SessionRoutingActor {
  
  /**
   * Create Props for an actor of this type
   * @param containerFactory A factory to create suitable container objects
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

  val router = new Router[ActorRef, RequestRoutable](token => sessionActor => msg => sessionActor ! msg.payload)
  val sessionMap = Map[SessionToken, SessionToken]() // Map LevelSession to LoginSession
  
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
      createSession(ctx, loginSession, levelInfo)
    case DeleteSession(ctx, loginSession, token) =>
      deleteSession(ctx, loginSession, token)
    case Terminated(sessionActor) =>
      terminateSession(sessionActor)
  }
  
  def createSession(ctx: RequestContext, login: SessionToken, levelInfo: SessionCreateRequest) = {
    log.info("Creating new session")
    
    val token: SessionToken = (login.toString + Random.alphanumeric.take(20).mkString).sha512.toString
    
    val sessionActor = context.actorOf(SessionActor.props(containerFactory, token))
    context.watch(sessionActor)
    
    // Update out state with the new route and session
    sessionMap += (token -> login)
    router.addRoute(token, sessionActor)
    
    // Send message to kick-start initialization proceedure
    log.info("Sending initialization message...")
    sessionActor ! InitializeSession(ctx, levelInfo)
  }
  
  def deleteSession(ctx: RequestContext, loginSession: LoginSession, token: SessionToken) = {
    log.info("Deleting session")
    sessionMap get token match {
        case Some(session) if session == loginSession =>
          deleteSessionActor(token) match {
            case true => ctx.complete((200, "Deleted session")) // TODO, add new message
            case false => ctx.complete((500, "Failed to delete session"))
          }
        case Some(session) => ctx.complete((403, "Not allowed to access that session"))
        case None => ctx.complete((404, "No such session exists"))
      }
  }
  
  def deleteSessionActor(token: SessionToken): Boolean = {
    // TODO, destroy container
    log.info("Deleting session: %token")
    router.getRoute(token) match {
      case Some(actor) => // TODO
    }
    router.removeRouteBySource(token)
  }
  
  /*
   * This is invoked when the underlying actor goes away
   */
  def terminateSession(sessionActor: ActorRef) = {
    log.info("Session terminated")
    router.removeRouteByDestination(sessionActor)
  }
}
