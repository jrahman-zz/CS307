package org.rahmanj

import akka.actor._
import spray.routing.RequestContext

import session._
import messages._
import routing._

case class CreateSession(ctx: RequestContext, login: LoginSession, command: ClientCreateSession)
case class DeleteSession(ctx: RequestContext, level: LevelSession)

class SessionRoutingActor extends Actor with ActorLogging {

  val router = new Router()
  
  def receive = {
    case msg: Routable =>
      router.routeMessage(msg)
    case CreateSession(ctx, loginSession, command) =>
      createSession(ctx, loginSession)
    case DeleteSession(ctx, levelSession) =>
      deleteSession(ctx, levelSession)
    case Terminated(sessionActor) =>
      terminateSession(sessionActor)
      
  }
  
  def createSession(ctx: RequestContext, login: LoginSession) = {
    log.info("Creating new session")
    
    val token = "TODO, create unique token"
    
    val sessionActor = context.actorOf(Props[SessionActor])
    context.watch(sessionActor)
    
    val levelSession = LevelSession(token, -1, -1, Python(), sessionActor, "TODO")
    
    router.addRoute((login, token), levelSession)
  }
  
  
  def deleteSession(ctx: RequestContext, levelSession: LevelSession) = {
    log.info("Deleting session")
    // TODO
  }
  
  def terminateSession(sessionActor: ActorRef) = {
    log.info("Session terminated")
    // TODO
  }
}
