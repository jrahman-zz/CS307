package org.rahmanj

import spray.routing._
import spray.routing.authentication.{Authentication,ContextAuthenticator}
import scala.concurrent.{Future,future}
import scala.concurrent.ExecutionContext
import scala.concurrent.ExecutionContext.Implicits.global

import session.LoginSession

trait DeviseAuthenticator extends ContextAuthenticator[LoginSession] {
  implicit def executionContext: ExecutionContext
  
  def apply(ctx: RequestContext): Future[Authentication[LoginSession]] = {
    authenticate(ctx)
  }
  
  def authenticate(ctx: RequestContext): Future[Authentication[LoginSession]]
}

class BasicDeviseAuthenticator(hostname: String, port: Int)(implicit val executionContext: ExecutionContext) extends DeviseAuthenticator {
  def authenticate(ctx: RequestContext): Future[Authentication[LoginSession]] = {
    future {
      Right(new LoginSession("jason", "test"))
    }
  }
}

object BasicDeviseAuthenticator {
  def apply(hostname: String, port: Int)(implicit settings: RoutingSettings, ec: ExecutionContext): BasicDeviseAuthenticator = {
    new BasicDeviseAuthenticator(hostname, port)
  }
}