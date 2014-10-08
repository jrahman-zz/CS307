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

trait Service extends HttpService {
	
  val sessionRouter = actorRefFactory.actorOf(Props[SessionRoutingActor])

  val serviceRoute = 
    path("") {
      get {
            complete("")
      }
    } ~
    path("submission") {
      post {
        ctx =>

      }
    } ~
    path("session") {
      post { // TODO, need authentication
        ctx =>
          sessionRouter ! CreateSession(ctx, LoginSession("TODO, create params here"))
      }
      get {
        complete("TODO")
      }	
    } ~
    path("ping") {
      get {
        complete("TODO, ping docker, and return reply")
      }
    }
}
