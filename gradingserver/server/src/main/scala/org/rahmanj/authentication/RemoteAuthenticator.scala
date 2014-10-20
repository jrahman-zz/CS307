package org.rahmanj.authentication

import scala.concurrent.{Future,ExecutionContext}

import spray.routing.RequestContext
import spray.routing.authentication.{Authentication,ContextAuthenticator}

import org.rahmanj.sessions.LoginSession

/**
 * TODO
 */
trait RemoteAuthenticator extends ContextAuthenticator[LoginSession] {
  implicit def executionContext: ExecutionContext
  
  def apply(ctx: RequestContext): Future[Authentication[LoginSession]] = {
    authenticate(ctx)
  }
  
  def authenticate(ctx: RequestContext): Future[Authentication[LoginSession]]
}