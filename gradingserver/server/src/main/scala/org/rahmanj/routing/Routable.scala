package org.rahmanj.routing

import spray.routing.RequestContext
import org.rahmanj.RequestCtx
import org.rahmanj.sessions._

trait Routable {
  type RouteSource
  type RoutableContext
  
  val source: RouteSource
  
  val context: RoutableContext
  
  val payload: Any
}

case class RequestRoutable(
  source: RouteSource,
  context: RoutableContext,
  payload: Any
) extends Routable {
  type RouteSource = SessionToken
  type RoutableContext = RequestCtx
}
