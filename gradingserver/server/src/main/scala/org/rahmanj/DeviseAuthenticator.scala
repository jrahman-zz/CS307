package org.rahmanj

import spray.routing._
import spray.routing.authentication.{Authentication,ContextAuthenticator}
import scala.concurrent.{Future,future}
import scala.concurrent.ExecutionContext
import scala.concurrent.ExecutionContext.Implicits.global

import session.{LoginSession, SessionToken}

trait RemoteAuthenticator extends ContextAuthenticator[LoginSession] {
  implicit def executionContext: ExecutionContext
  
  def apply(ctx: RequestContext): Future[Authentication[LoginSession]] = {
    authenticate(ctx)
  }
  
  def authenticate(ctx: RequestContext): Future[Authentication[LoginSession]]
}

class DeviseAuthenticator(hostname: String, port: Int, token: String)(implicit val executionContext: ExecutionContext) extends RemoteAuthenticator {
  def authenticate(ctx: RequestContext): Future[Authentication[LoginSession]] = {
    Future {
      // TODO, return a future from a request to the app server
      // TODO, use the token
      Right(LoginSession("jason", "test"))
    }
  }
}

object DeviseAuthenticator {
  def apply(hostname: String, port: Int, token: SessionToken)(implicit settings: RoutingSettings, ec: ExecutionContext): DeviseAuthenticator = {
    new DeviseAuthenticator(hostname, port, token)
  }
}