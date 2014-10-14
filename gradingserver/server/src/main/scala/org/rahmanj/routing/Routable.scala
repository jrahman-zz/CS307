package org.rahmanj.routing

import spray.routing.RequestContext
import org.rahmanj.session._

case class Routable (
  ctx: RequestContext,
  login: LoginSession,
  token: SessionToken,
  payload: Any
)
