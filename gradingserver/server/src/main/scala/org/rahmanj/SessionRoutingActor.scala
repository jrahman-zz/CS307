package org.rahmanj

import scala.collection.mutable.Map
import akka.actor._
import spray.routing.RequestContext

import session.{LevelSession,LoginSession}

case class CreateSession(ctx: RequestContext, loginSession: LoginSession)
case class DeleteSession(ctx: RequestContext, levelSession: LevelSession)

class SessionRoutingActor extends Actor with ActorLogging {

  val sessionActors: Map[LevelSession, ActorRef] = Map()
  val actorSessions: Map[ActorRef, LevelSession] = Map()
  val userSessions: Map[LoginSession, List[LevelSession]] = Map() // TODO, create this
  
  def receive = {
    case CreateSession(ctx, loginSession) =>
      createSession(ctx, loginSession)
    case DeleteSession(ctx, levelSession) =>
      deleteSession(ctx, levelSession)
    case Terminated(sessionActor) =>
      terminateSession(sessionActor)
      
  }
  
  def createSession(ctx: RequestContext, loginSession: LoginSession) = {
    //TODO, create level session
    log.info("Creating new session")
    val sessionActor = context.actorOf(Props[SessionActor])
    context.watch(sessionActor)
  }
  
  def deleteSession(ctx: RequestContext, levelSession: LevelSession) = {
    //TODO, delete session here
    log.info("Deleting session")
  }
  
  def terminateSession(sessionActor: ActorRef) = {
    log.info("Session terminated")
    actorSessions.remove(sessionActor) match {
      case Some(s) => sessionActors.remove(s)
      case None => log.info("Invalid session")
    }
  }
}
