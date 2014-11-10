package org.rahmanj

import akka.actor._

import scala.concurrent.Future
import scala.concurrent.ExecutionContext.Implicits.global

import spray.routing._

import sessions._
import messages._
import routing._
import container._

/** Represents the core functionality being the service
 *
 *  Implements abstract functionality in ServiceRoutes through dependency injection
 *  of the authenticatorFactory, actorRefFactory, and sessionRouter dependencies 
 */
class ServiceActor extends Actor with ServiceRoutes {
  
  val system = ActorSystem()
 
  
  val sessionRouter = actorRefFactory.actorOf(SessionRoutingActor.props(new ProcessContainerFactory()))
  
  /** The [[spray.routing.HttpServer]] trait only requires this member be implemented
   *
   */
  def actorRefFactory = context

  /** This actor only runs routes for the service
   *
   *  Invoke the route upon receiving a message
   */
  def receive = runRoute(serviceRoute)
}


