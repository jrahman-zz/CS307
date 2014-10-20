package org.rahmanj

import spray.routing.RequestContext
import org.rahmanj.sessions.LoginSession

/** A context for a given request being routed
 * 
 * @constructor create a new RequestCtx
 * @param ctx The Spray RequestContext
 * @param login The login session for the context
 */
case class RequestCtx(
  ctx: RequestContext,
  login: LoginSession
)
