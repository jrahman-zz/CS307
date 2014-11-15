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
 * @tparam Destination The type of the route final destination
 * @tparam Message Subclass of [[Routable]] that will be routed
 * @param routeAction Actually performs the task of routing the message to the final destination
 */
class Router[Destination, Message <: Routable](routeAction: Message#RouteSource => Destination => Message => Unit) {
  
  type Source = Message#RouteSource
  
  val routes: Map[Source, Destination] = Map[Source, Destination]()
  val reverseRoutes: Map[Destination, Source] = Map[Destination, Source]()
  
  /** Add a new route to the router
   * 
   * @param src The route source
   * @param dest The route destination
   */
  def addRoute(src: Source, dest: Destination) = {
    routes += (src -> dest)
    reverseRoutes += (dest -> src)
  }
  
  /** Add a new route to the router
   * 
   */
  def +=(that: Tuple2[Source, Destination]) = {
    this.addRoute(that._1, that._2)
    this
  }
  
   /** Get the route destination by source
    * 
    * @param src The source to search for a destination
    * @returns An [[Option[Destination]]] with either None or Some(Destination)
    */
  def getRoute(src: Source): Option[Destination] = {
    routes get src
  }
  
    /** Remove a route from the router by the source
     * 
     * @param src The source of the route to be removed
     * @returns true if the route existed and was removed, false otherwise
     */
  def removeRouteBySource(src: Source): Boolean = {
    routes get src match {
      case Some(dest) =>
        reverseRoutes - dest
        routes -= src
        true
      case None => false
    }
  }
  
  /** Remove a route from the router by the destination
   * 
   * @param dest The destination of the route to remove
   * @returns true if the route existed and was removed, otherwise false
   */
  def removeRouteByDestination(dest: Destination): Boolean = {
    reverseRoutes get dest match {
      case Some(src) =>
        routes -= src
        reverseRoutes -= dest
        true
      case None => false
    }
  }
  
  /** Actually route a message to the destination
   *  Note that the routeAction is invoked with the message, source, and destination
   *  as parameters upon a successful route match
   * 
   * @param msg The mesage to be routed to the destination
   * @returns true if the message was successfully routed, false otherwise
   */
  def routeMessage(msg: Message): Boolean = {
    getRoute(msg.source) match {
      case Some(destination) =>
        routeAction(msg.source)(destination)(msg)
        true
      case None => false
    } 
  }
}