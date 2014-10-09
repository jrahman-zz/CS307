package org.rahmanj

import akka.actor._
import scala.concurrent.ExecutionContext.Implicits.global
import spray.routing._
import spray.http._

import session.LoginSession

// Separate the route structure from the actual actor
class ServiceActor extends Actor with Service {
  
  // The HTTP Service trait only requires this abstract member
  def actorRefFactory = context

  // This actor only runs routes for the service
  def receive = runRoute(serviceRoute)
}

trait Service extends HttpService {
	
  val sessionRouter = actorRefFactory.actorOf(Props[SessionRoutingActor])

  val system = ActorSystem()
  
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
      authenticate(BasicDeviseAuthenticator(
          Settings(system).AppServer.Hostname,
          Settings(system).AppServer.Port)
        ) {
        loginSession =>
        post { // TODO, need authentication
          ctx =>
            sessionRouter ! CreateSession(ctx, new LoginSession("jason", "test"))
        }
        get {
          ctx =>
            complete("TODO")
        }
      }	
    } ~
    path("ping") {
      get {
        complete("TODO, ping docker, and return reply")
      }
    }
}
