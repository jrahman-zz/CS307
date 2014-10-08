package org.rahmanj

import scala.collection.mutable.Map
import akka.actor._
import spray.routing.RequestContext

case class CreateSession(ctx: RequestContext, login: LoginSession)
case class DeleteSession(levelSession: LevelSession)

class SessionRoutingActor extends Actor {

  val sessions: Map[LevelSession, ActorRef] = Map()
  
  def receive = {
    case CreateSession(ctx, LoginSession("username")) =>
      "TODO"
    case DeleteSession(levelSession) =>
      "TODO"
    case Terminated(session) =>
      "TODO Remove terminated session from the map"
  }
  
  def createSession(login: LoginSession) = {
    "TODO, create level session"
    val session = new LevelSession("test", Python)
    val sessionActor = context.actorOf(Props[SessionActor])
    context.watch(sessionActor)
  }
}
