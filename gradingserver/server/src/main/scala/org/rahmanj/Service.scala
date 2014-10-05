package org.rahmanj

import akka.actor._
import scala.concurrent.ExecutionContext.Implicits.global
import spray.routing._
import spray.http._

// Separate the route structure from the actual actor
class ServiceActor extends Actor with Service {

  // The HTTP Service trait only requires this abstract member
  def actorRefFactory = context

  // This actor only runs routes for the service
  def receive = runRoute(serviceRoute)
}

case class DeadContainer(id: Int)

class CometActor extends Actor {

  def receive = {
          case DeadContainer(id) => "test"
  }
}

trait Service extends HttpService {
	
val cometActor = actorRefFactory.actorOf(Props[CometActor])

val serviceRoute = 
  path("") {
    get {
          complete("")
    }
  } ~
  path("submission") {
    post {
            complete("TODO")
    }
  }
  path("session") {
    post {
            complete("TODO")
    }
    get {
            complete("TODO")
    }	
  }
}
