package org.rahmanj.routing

import spray.routing.RequestContext
import org.rahmanj.session._

case class Routable[RoutableContext, RouteSource] (
  source: RouteSource,
  context: RoutableContext,
  payload: Any
)
