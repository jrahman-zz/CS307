package org.rahmanj.routing

import spray.routing.RequestContext
import org.rahmanj.session.LoginSession

case class RequestCtx(
  ctx: RequestContext,
  login: LoginSession
)
