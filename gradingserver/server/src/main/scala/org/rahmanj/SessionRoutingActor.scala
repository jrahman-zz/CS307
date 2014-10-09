package org.rahmanj

import scala.collection.mutable.Map
import akka.actor._
import spray.routing.RequestContext

case class CreateSession(ctx: RequestContext, login: Any)
case class DeleteSession(levelSession: Any)

class SessionRoutingActor extends Actor with ActorLogging {

  //val sessions: Map[LevelSession, ActorRef] = Map()
  //val actors: Map[ActorRef, LevelSession] = Map()
  val sessions: Map[Any, ActorRef] = Map()
  val actors: Map[ActorRef, Any] = Map()
  
  def receive = {
    case CreateSession(ctx, loginSession) =>
      "TODO"
    case DeleteSession(levelSession) =>
      "TODO"
    case Terminated(sessionActor) =>
      log.info("Session terminated")
      val session = actors.remove(sessionActor)
      actors.remove(session)
      
  }
  
  def createSession = {
    "TODO, create level session"
    val sessionActor = context.actorOf(Props[SessionActor])
    context.watch(sessionActor)
  }
}
