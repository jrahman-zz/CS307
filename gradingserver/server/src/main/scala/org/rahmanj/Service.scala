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
        decompressRequest() {
          pathPrefix("level" /) {
            path("reset" / RestPath) { sessionToken =>
              val token = sessionToken.toString
              post { ctx =>
                sessionRouter ! Routable(token, RequestCtx(ctx, login), ClientResetLevel())
              }
            } ~
            path("submit" / RestPath) { sessionToken =>
              val token: SessionToken = sessionToken.toString
              post {
                import ClientLevelSubmissionProtocol._
                entity(as[ClientLevelSubmission]) { submission => {
                    ctx: RequestContext =>
                      sessionRouter ! Routable(token, RequestCtx(ctx, login), submission)
                  }
                }
              }
            }
          } ~
          pathPrefix("challenge" /) {
            path("submit" / RestPath) { sessionToken =>
              val token = sessionToken.toString
              post {
                import ClientChallengeSubmissionProtocol._
                entity(as[ClientChallengeSubmission]) { submission => {
                    ctx: RequestContext => 
                      sessionRouter ! Routable(token, RequestCtx(ctx, login), submission)
                  }
                }
              }
            }
          }~
          pathPrefix("session" /) {
            path("delete" / RestPath) { sessionToken =>
              val token = sessionToken.toString
              post { ctx =>
                sessionRouter ! Routable(token, RequestCtx(ctx, login), ClientDeleteSession())
              }
            } ~
            path("create") {
              // TODO, do we want to define the class and langauge when doing this
              post {
                import ClientCreateSessionProtocol._
                entity(as[ClientCreateSession]) { sessionInfo => {
                    ctx: RequestContext =>
                      sessionRouter ! CreateSession(ctx, login, sessionInfo)
                  }
                }
              }
            }
          }
        }
      }
    } ~
    path("ping") {
      get {
        complete("TODO, ping docker, and return reply")
      }
    }
}
