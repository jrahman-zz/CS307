package org.rahmanj.routing

import spray.routing.RequestContext
import org.rahmanj.RequestCtx
import org.rahmanj.sessions._

trait Routable {
  type RouteSource
  type RoutableContext
  
  def source: RouteSource
  def context: RoutableContext
  
  def payload: Any
}

case class RequestRoutable(
  source: RequestRoutable#RouteSource,
  context: RequestRoutable#RoutableContext,
  payload: Any
) extends Routable {
  type RouteSource = SessionToken
  type RoutableContext = RequestCtx
}
