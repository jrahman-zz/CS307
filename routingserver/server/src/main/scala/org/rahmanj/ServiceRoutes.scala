package org.rahmanj

import akka.actor._

import scala.concurrent.Future
import scala.concurrent.ExecutionContext.Implicits.global

import spray.routing.authentication.{Authentication,ContextAuthenticator}
import spray.routing._
import spray.http._

import spray.httpx.SprayJsonSupport._

import sessions._
import routing._
import messages._

/** Provides the routes for our services
 * @requires sessionRouter An ActorRef for a message routing actor
 * @requires authenticatorFactory A function returning a [[spray.routing.authentication.ContextAuthenticator]]
 */
trait ServiceRoutes extends HttpService {
	
  val sessionRouter: ActorRef
  
  val serviceRoute =
    headerValueByName("user_token") { loginToken =>
      pathPrefix("level") {
        path("reset" / Segment) { sessionToken =>
          val token = sessionToken.toString
          post { ctx =>
            sessionRouter ! RequestRoutable(token, RequestCtx(ctx, loginToken), SessionResetRequest())
          } ~
          complete((405, "Invalid method, only post allowed"))
        } ~
        path("submit" / Segment) { sessionToken =>
          val token: SessionToken = sessionToken.toString
          post {
            import LevelSubmissionRequestProtocol._
            entity(as[LevelSubmissionRequest]) { submission => {
                ctx: RequestContext =>
                  sessionRouter ! RequestRoutable(token, RequestCtx(ctx, loginToken), Submission(ctx, submission))
              }
            }  ~ complete((400, "Incorrect request body"))
          } ~ complete((405, "Invalid method, only post allowed"))
        }
      } ~
      pathPrefix("challenge") {
        path("submit" / Segment) { sessionToken =>
          val token = sessionToken.toString
          post {
            import ChallengeSubmissionRequestProtocol._
            entity(as[ChallengeSubmissionRequest]) { submission => {
                ctx: RequestContext => 
                  sessionRouter ! RequestRoutable(token, RequestCtx(ctx, loginToken), Submission(ctx, submission))
              }
            }  ~ complete((400, "Incorrect request body"))
          } ~ complete((405, "Invalid method, only post allowed"))
        }
      }~
      pathPrefix("session") {
        path("create") {
          post {
            entity(as[String]) { sessionInfo => {
                ctx => sessionRouter ! CreateSession(ctx, loginToken, SessionCreateRequest(sessionInfo))
              }
            } ~ complete((400, "Incorrect request body"))
          } ~ complete((405, "Invalid method, only post allowed"))
        } ~
        path("delete" / Segment) { sessionToken =>
          post {
            ctx => sessionRouter ! DeleteSession(ctx, loginToken, sessionToken.toString)
          } ~ complete((405, "Invalid method, only post allowed"))
        }
      } 
    } ~
    path("ping") {
      get {
        complete((200, "pong"))
      } ~ complete((405, "Invalid method, only get allowed"))
    } ~ complete((500, "This is not the page you are looking for"))
}
