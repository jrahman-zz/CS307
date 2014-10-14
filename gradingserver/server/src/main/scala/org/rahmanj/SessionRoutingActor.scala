package org.rahmanj

import scala.util.Random

import akka.actor._
import spray.routing.RequestContext

import scala.collection.mutable.Map
import com.roundeights.hasher.Implicits._

import session._
import messages._
import routing._

case class CreateSession(ctx: RequestContext, login: LoginSession, levelInfo: ClientCreateSession)
case class DeleteSession(ctx: RequestContext, login: LoginSession, token: SessionToken)

class SessionRoutingActor extends Actor with ActorLogging {

  val router = new Router()
  val sessionMap = new Map[SessionToken, LoginSession]()
  
  def receive = {
    case msg: Routable =>
      sessionMap get msg.token match {
        case Some(session) if session == msg.login => router.routeMessage(msg)
        case Some(session) => msg.ctx.complete((403, "Not allowed to access that session"))
        case None => msg.ctx.complete((404, "No such session exists"))
      }
    case CreateSession(ctx, loginSession, levelInfo) =>
      createSession(ctx, loginSession, levelInfo)
    case DeleteSession(ctx, loginSession, token) =>
      sessionMap get token match {
        case Some(session) if session == loginSession => deleteSession(ctx, token)
        case Some(session) => ctx.complete((403, "Not allowed to access that session"))
        case None => ctx.complete((404, "No such session exists"))
      }
    case Terminated(sessionActor) =>
      terminateSession(sessionActor)
  }
  
  def createSession(ctx: RequestContext, login: LoginSession, levelInfo: ClientCreateSession) = {
    log.info("Creating new session")
    
    val token = (login.toString + Random.alphanumeric.take(20).mkString).sha512
    
    val sessionActor = context.actorOf(Props[SessionActor])
    context.watch(sessionActor)
    
    // Update out state with the new route and session
    sessionMap += (token -> login)
    router.addRoute(token, sessionActor)
    
    // Send message to kick-start initialization proceedure
    sessionActor ! InitializeSession(ctx, levelInfo)
  }
  
  
  def deleteSession(ctx: RequestContext, token: SessionToken) = {
    log.info("Deleting session")
    // TODO
    
    
  }
  
  def terminateSession(sessionActor: ActorRef) = {
    log.info("Session terminated")
    // TODO
  }
}
