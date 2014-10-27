package org.rahmanj

import akka.actor._

import scala.concurrent.Future
import scala.concurrent.ExecutionContext.Implicits.global

import spray.routing._
import spray.routing.authentication.{Authentication,ContextAuthenticator}

import sessions._
import messages._
import routing._
import container._
import authentication._

/** Represents the core functionality being the service
 *
 *  Implements abstract functionality in ServiceRoutes through dependency injection
 *  of the authenticatorFactory, actorRefFactory, and sessionRouter dependencies 
 */
class ServiceActor extends Actor with ServiceRoutes {
  
  val system = ActorSystem()
  
  /** Implements abstract method in ServiceRoutes
   * 
   *  Builds the appropriate authenticator using our own environment
   */
  def authenticatorFactory(token: SessionToken): (RequestContext => Future[Authentication[LoginSession]]) = {
    DummyAuthenticator(true, token) // TODO, update with DeviseAuthenticator when ready
  }
  
  val sessionRouter = actorRefFactory.actorOf(SessionRoutingActor.props(new DummyContainerFactory()))
  
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


