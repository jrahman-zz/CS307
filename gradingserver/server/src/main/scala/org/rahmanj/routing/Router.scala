package org.rahmanj.routing

import akka.actor.ActorRef
import akka.event.Logging

import scala.collection.mutable.Map

import org.rahmanj.sessions._


/** Routes messages from a [[RouteSource]] to a [[RouteDestination]]
 * 
 *  Routes messages from a [[RouteSource]] to a [[RouteDestination]] and
 *  applies the given action to perform the actual routing operation
 * 
 * @constructor Creates a new instance of the [[Router]]
 * @param routeAction Actually performs the task of routing the message to the final destination
 */
class Router[Destination, Message <: Routable](routeAction: Message#RouteSource => Destination => Message => Unit) {
  
  type Source = Message#RouteSource
  
  val routes: Map[Source, Destination] = Map[Source, Destination]()
  val reverseRoutes: Map[Destination, Source] = Map[Destination, Source]()
  
  def addRoute(src: Source, dest: Destination) = {
    routes += (src -> dest)
    reverseRoutes += (dest -> src)
  }
  
  def +=(that: Tuple2[Source, Destination]) = {
    this.addRoute(that._1, that._2)
    this
  }
  
  def getRoute(src: Source): Option[Destination] = {
    routes get src
  }
  
  def removeRouteBySource(src: Source): Boolean = {
    routes get src match {
      case Some(dest) =>
        reverseRoutes - dest
        routes -= src
        true
      case None => false
    }
  }
  
  def removeRouteByDestination(dest: Destination): Boolean = {
    reverseRoutes get dest match {
      case Some(src) =>
        routes -= src
        reverseRoutes -= dest
        true
      case None => false
    }
  }
  
  def routeMessage(msg: Message): Boolean = {
    getRoute(msg.source) match {
      case Some(destination) =>
        routeAction(msg.source)(destination)(msg)
        true
      case None => false
    } 
  }
}