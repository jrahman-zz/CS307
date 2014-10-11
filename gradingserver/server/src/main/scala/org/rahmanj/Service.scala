package org.rahmanj

import akka.actor._
import scala.concurrent.ExecutionContext.Implicits.global
import spray.routing._
import spray.http._

import spray.httpx.SprayJsonSupport.sprayJsonMarshaller
import spray.httpx.SprayJsonSupport.sprayJsonUnmarshaller

import session._
import gameplay._

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
          pathPrefix("level/reset" / RestPath) { sessionToken =>
            val token = sessionToken.toString
            post { ctx =>
              sessionRouter ! Routable(ctx, login, token, ClientResetLevel())
            }
          } ~
          pathPrefix("level/submit" / RestPath) { sessionToken =>
            val token = SessionToken(sessionToken.toString)
            post { ctx =>
              entity(as[ClientLevelSubmission]) { submission =>
                sessionRouter ! Routable(ctx, login, token, submission)
              }
            }
          } ~
          pathPrefix("challenge/submit" / RestPath) { sessionToken =>
            val token = sessionToken.toString
            post { ctx =>
              entity(as[ClientChallengeSubmission]) { submission =>
                sessionRouter ! Routable(ctx, login, token, submission)
              }
            }
          } ~
          path("session/delete" / RestPath) { sessionToken =>
            val token = sessionToken.toString
            post { ctx =>
              sessionRouter ! Routable(ctx, login, ClientDeleteSession())
            }
          } ~
          path("session/create") {
            // TODO, do we want to define the class and langauge when doing this
            post { ctx =>
              entity(as[ClientCreateSession]) { sessionInfo =>
                sessionRouter ! CreateSession(ctx, login, sessionInfo)
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
