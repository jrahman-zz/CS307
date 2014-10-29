package org.rahmanj.authentication

import scala.concurrent.{Future,ExecutionContext}
import scala.concurrent.ExecutionContext.Implicits.global

import spray.routing.RequestContext
import spray.routing.authentication.Authentication

import org.rahmanj.sessions.{LoginSession, SessionToken}

object DeviseAuthenticator {
  def apply(hostname: String, port: Int, token: SessionToken)(implicit ec: ExecutionContext): RemoteAuthenticator = {
    new DeviseAuthenticator(hostname, port, token)
  }
  
  private class DeviseAuthenticator(hostname: String, port: Int, token: String)(implicit val executionContext: ExecutionContext) extends RemoteAuthenticator {
    def authenticate(ctx: RequestContext): Future[Authentication[LoginSession]] = {
      Future {
        // TODO, return a future from a request to the app server
        // TODO, use the token
        Right(LoginSession("jason", "test"))
      }
    }
  }
}