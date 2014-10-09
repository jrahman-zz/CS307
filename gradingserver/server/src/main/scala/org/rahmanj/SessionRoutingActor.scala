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
    case ResetSession(ctx, levelSession) =>
      resetSession(ctx, levelSession)
    case Terminated(sessionActor) =>
      terminateSession(sessionActor)
      
  }
  
  def createSession(ctx: RequestContext, loginSession: LoginSession) = {
    log.info("Creating new session")
    
    val levelSession = LevelSession("TODO, create unique token", -1, -1, new Python())
    
    // TODO, inject level session into sessionActor
    val sessionActor = context.actorOf(Props[SessionActor])
    context.watch(sessionActor)
    
    sessionActors.add(levelSession, sessionActor)
    actorSessions.add(sessionActor, levelSession)
    userSessions.get(loginSession) match {
      case Some(list) => userSessions.get(loginSession).add()
      case None => userSessions.add(loginSession, List(levelSession))
    }
  }
  
  def deleteSession(ctx: RequestContext, levelSession: LevelSession) = {
    //TODO, delete session here
    log.info("Deleting session")
  }
  
  def resetSession(ctx: RequestContext, levelSession: LevelSession) = {
    log.info("Resetting session")
  }
  
  def terminateSession(sessionActor: ActorRef) = {
    log.info("Session terminated")
    actorSessions.remove(sessionActor) match {
      case Some(s) => sessionActors.remove(s)
      case None => log.info("Invalid session")
    }
  }
}
