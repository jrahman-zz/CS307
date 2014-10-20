package org.rahmanj.routing

import akka.event.Logging

import scala.collection.mutable.Map

import org.rahmanj.sessions._

class Router[RouteSource, RouteDestination, RoutableContext](routeAction: RouteSource => RouteDestination => Routable[RoutableContext, RouteSource] => Unit) {
  
  val routes: Map[RouteSource, RouteDestination] = Map[RouteSource, RouteDestination]()
  val reverseRoutes: Map[RouteDestination, RouteSource] = Map[RouteDestination, RouteSource]()
  
  def addRoute(src: RouteSource, dest: RouteDestination) = {
    routes += (src -> dest)
    reverseRoutes += (dest -> src)
  }
  
  def +=(that: Tuple2[RouteSource, RouteDestination]) = {
    this.addRoute(that._1, that._2)
    this
  }
  
  def getRoute(src: RouteSource): Option[RouteDestination] = {
    routes get src
  }
  
  def removeRouteBySource(src: RouteSource): Boolean = {
    routes get src match {
      case Some(dest) =>
        reverseRoutes - dest
        routes -= src
        true
      case None => false
    }
  }
  
  def removeRouteByDestination(dest: RouteDestination): Boolean = {
    reverseRoutes get dest match {
      case Some(src) =>
        routes -= src
        reverseRoutes -= dest
        true
      case None => false
    }
  }
  
  def routeMessage(msg: Routable[RoutableContext, RouteSource]): Boolean = {
    getRoute(msg.source) match {
      case Some(destination) =>
        routeAction(msg.source)(destination)(msg)
        true
      case None => false
    } 
  }
}
