package org.rahmanj.routing

import scala.collection.mutable.Map
import org.rahmanj.session._

class Router {
  
  val routes: Map[RouteSource, RouteDestination] = Map[RouteSource, RouteDestination]()
  val reverseRoutes: Map[RouteDestination, RouteSource] = Map[RouteDestination, RouteSource]()
  
  def addRoute(src: RouteSource, dest: RouteDestination) = {
    routes + (src -> dest)
    reverseRoutes + (dest -> src)
  }
  
  def getRoute(src: RouteSource): Option[RouteDestination] = {
    routes get src
  }
  
  def removeRoute(src: RouteSource) = {
    routes get src match {
      case Some(dest) =>
        reverseRoutes - dest
        routes - src
    }
  }
  
  def removeRoute(dest: RouteDestination) = {
    reverseRoutes get dest match {
      case Some(src) =>
        routes - src
        reverseRoutes - dest
    }
  }
  
  def routeMessage(msg: Routable) = {
    getRoute((msg.login, msg.token)) match {
      case Some(sessionActor) =>
        sessionActor ! msg.payload
      case _ =>
        msg.ctx.complete("404") // TODO, send correct error
    } 
  }
}
