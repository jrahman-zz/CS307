package org.rahmanj.authentication

import scala.concurrent.{Future,ExecutionContext}

import spray.routing.RequestContext
import spray.routing.authentication.{Authentication,ContextAuthenticator}

import org.rahmanj.sessions.LoginSession

/** [[RemoteAuthenticator]] represents a remote source of authentication information
 * 
 * @required executionContext Must be supplied in extending class
 * @required authenticate Must be implemented in extending class
 */
trait RemoteAuthenticator extends ContextAuthenticator[LoginSession] {
  implicit def executionContext: ExecutionContext
  
  def apply(ctx: RequestContext): Future[Authentication[LoginSession]] = {
    authenticate(ctx)
  }
  
  def authenticate(ctx: RequestContext): Future[Authentication[LoginSession]]
}