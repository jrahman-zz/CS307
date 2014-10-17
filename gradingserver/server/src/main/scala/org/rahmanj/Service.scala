package org.rahmanj

import akka.actor._
import scala.concurrent.ExecutionContext.Implicits.global
import spray.routing._
import spray.http._

import spray.httpx.SprayJsonSupport.sprayJsonMarshaller
import spray.httpx.SprayJsonSupport.sprayJsonUnmarshaller

import session._
import messages._
import routing._

case class ClientDeleteSession() // TODO, find better place for this

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
  
  val appserverHostname = Settings(system).AppServer.Hostname
  val appserverPort = Settings(system).AppServer.Port
  
  val serviceRoute =
    headerValueByName("devise_token") { authToken =>
      authenticate(DeviseAuthenticator(appserverHostname, appserverPort, authToken)) { login =>
        pathPrefix("level") {
          path("reset" / RestPath) { sessionToken =>
            val token = sessionToken.toString
            post { ctx =>
              sessionRouter ! Routable(token, RequestCtx(ctx, login), ClientResetLevel())
            } ~
            complete((405, "Invalid method, only post allowed"))
          } ~
          path("/submit" / RestPath) { sessionToken =>
            val token: SessionToken = sessionToken.toString
            post {
              import ClientLevelSubmissionProtocol._
              entity(as[ClientLevelSubmission]) { submission => {
                  ctx: RequestContext =>
                    sessionRouter ! Routable(token, RequestCtx(ctx, login), submission)
                }
              }  ~ complete((400, "Incorrect request body"))
            } ~ complete((405, "Invalid method, only post allowed"))
          }
        } ~
        pathPrefix("challenge") {
          path("submit" / RestPath) { sessionToken =>
            val token = sessionToken.toString
            post {
              import ClientChallengeSubmissionProtocol._
              entity(as[ClientChallengeSubmission]) { submission => {
                  ctx: RequestContext => 
                    sessionRouter ! Routable(token, RequestCtx(ctx, login), submission)
                }
              }  ~ complete((400, "Incorrect request body"))
            } ~ complete((405, "Invalid method, only post allowed"))
          }
        }~
        pathPrefix("session") {
          path("delete" / RestPath) { sessionToken =>
            val token = sessionToken.toString
            post { ctx =>
              sessionRouter ! Routable(token, RequestCtx(ctx, login), ClientDeleteSession())
            } ~ complete((405, "Invalid method, only post allowed"))
          } ~
          path("create") {
            post {
              import ClientCreateSessionProtocol._
              entity(as[ClientCreateSession]) { sessionInfo => {
                  ctx: RequestContext =>
                    sessionRouter ! CreateSession(ctx, login, sessionInfo)
                }
              } ~ complete((400, "Incorrect request body"))
            } ~ complete((405, "Invalid method, only post allowed"))
          }
        } ~ complete((404, "This is not the page you are looking for"))
      } ~ complete((401, "Who are you?"))
    } ~
    path("ping") {
      get {
        complete("TODO, ping docker, and return reply")
      }
    } ~ complete((404, "This is not the page you are looking for"))
}
