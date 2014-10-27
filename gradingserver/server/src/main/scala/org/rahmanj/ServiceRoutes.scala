package org.rahmanj

import akka.actor._

import scala.concurrent.Future
import scala.concurrent.ExecutionContext.Implicits.global

import spray.routing.authentication.{Authentication,ContextAuthenticator}
import spray.routing._
import spray.http._

import spray.httpx.SprayJsonSupport.sprayJsonMarshaller
import spray.httpx.SprayJsonSupport.sprayJsonUnmarshaller

import sessions._
import routing._
import messages._

/** Provides the routes for our services
 * @requires sessionRouter An ActorRef for a message routing actor
 * @requires authenticatorFactory A function returning a [[spray.routing.authentication.ContextAuthenticator]]
 */
trait ServiceRoutes extends HttpService {
	
  val sessionRouter: ActorRef  
  def authenticatorFactory(token: SessionToken): (RequestContext => Future[Authentication[LoginSession]])
  
  val serviceRoute =
    headerValueByName("user_token") { loginToken =>
      pathPrefix("level") {
        path("reset" / RestPath) { sessionToken =>
          val token = sessionToken.toString
          post { ctx =>
            sessionRouter ! RequestRoutable(token, RequestCtx(ctx, loginToken), SessionResetRequest())
          } ~
          complete((405, "Invalid method, only post allowed"))
        } ~
        path("submit" / RestPath) { sessionToken =>
          val token: SessionToken = sessionToken.toString
          post {
            import LevelSubmissionRequestProtocol._
            entity(as[LevelSubmissionRequest]) { submission => {
                ctx: RequestContext =>
                  sessionRouter ! RequestRoutable(token, RequestCtx(ctx, loginToken), submission)
              }
            }  ~ complete((400, "Incorrect request body"))
          } ~ complete((405, "Invalid method, only post allowed"))
        }
      } ~
      pathPrefix("challenge") {
        path("submit" / RestPath) { sessionToken =>
          val token = sessionToken.toString
          post {
            import ChallengeSubmissionRequestProtocol._
            entity(as[ChallengeSubmissionRequest]) { submission => {
                ctx: RequestContext => 
                  sessionRouter ! RequestRoutable(token, RequestCtx(ctx, loginToken), submission)
              }
            }  ~ complete((400, "Incorrect request body"))
          } ~ complete((405, "Invalid method, only post allowed"))
        }
      }~
      pathPrefix("session") {
        path("delete" / RestPath) { sessionToken =>
          val token = sessionToken.toString
          post { ctx =>
            sessionRouter ! RequestRoutable(token, RequestCtx(ctx, loginToken), SessionDeleteRequest())
          } ~ complete((405, "Invalid method, only post allowed"))
        } ~
        path("create") {
          post {
            import SessionCreateRequestProtocol._
            entity(as[SessionCreateRequest]) { sessionInfo => {
                ctx: RequestContext =>
                  sessionRouter ! CreateSession(ctx, loginToken, sessionInfo)
              }
            } ~ complete((400, "Incorrect request body"))
          } ~ complete((405, "Invalid method, only post allowed"))
        }
      } 
    } ~
    path("ping") {
      get {
        complete("TODO, ping docker, and return reply")
      } ~ complete((405, "Invalid method, only get allowed"))
    } ~ complete((404, "This is not the page you are looking for"))
}
