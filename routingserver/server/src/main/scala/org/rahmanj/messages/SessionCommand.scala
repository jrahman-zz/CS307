package org.rahmanj.messages

import org.rahmanj.containers.Container
import org.rahmanj.sessions.{LoginSession, SessionToken}
import spray.routing.RequestContext

case class DeleteSession(
  /*
   * Incoming request context for returning a response
   */
  ctx: RequestContext,
  
  /*
   * Login token to identify the user creating the new session
   */
  login: SessionToken,
  
  /*
   * Unique session identifier
   */
  token: SessionToken
)

case class CreateSession(
  /*
   * Incoming request context for returning a response
   */
  ctx: RequestContext,
  
  /*
   * Unique session identifier
   */
  login: SessionToken,
  
  /*
   * Incoming request body to initialize the container
   */
  request: SessionCreateRequest
)

case class InitializeSession(
  /*
   * Incoming request context for returning a response
   */
  ctx: RequestContext,
  
  /*
   * Incoming request body to initialize the container
   */
  request: SessionCreateRequest,
  
  /*
   * Unique session identifier
   */
  token: SessionToken

)
case class SessionInitialized(
  /*
   * Incoming request context for returning a response
   */
  ctx: RequestContext,
  
  /*
   * Initialized container ready for use
   */
  container: Container
)
