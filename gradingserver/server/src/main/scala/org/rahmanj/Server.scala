package org.rahmanj

import akka.actor.ActorSystem
import akka.actor.Props
import spray.can.Http
import spray.can.Http.Bind

import akka.io.IO

/** Bootstrap object to start the server. */
object Bootstrap extends App {
  
  implicit val system = ActorSystem("server")
  
  val service = system.actorOf(Props[ServiceActor], "service")
  
  IO(Http) ! Bind(listener = service, interface = Settings(system).Http.Interface, port = Settings(system).Http.Port)
}
