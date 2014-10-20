package org.rahmanj.authentication

import scala.concurrent.{Future,ExecutionContext}
import scala.concurrent.ExecutionContext.Implicits.global

import spray.routing._
import spray.routing.AuthenticationFailedRejection._
import spray.routing.authentication.Authentication

import org.rahmanj.sessions.{LoginSession, SessionToken}

object DummyAuthenticator {
  def apply(truth: Boolean, token: SessionToken)(implicit settings: RoutingSettings, ec: ExecutionContext): RemoteAuthenticator = {
    new DummyAuthenticator(truth, token)
  }
  
  private class DummyAuthenticator(truth: Boolean, token: SessionToken)(implicit val executionContext: ExecutionContext) extends RemoteAuthenticator {
    def authenticate(ctx: RequestContext): Future[Authentication[LoginSession]] = {
      Future {
        truth match {
          case true => Right(LoginSession("jason", "test"))
          case false => Left(AuthenticationFailedRejection(CredentialsRejected, List()))
        }
        
      }
    }
  }
}