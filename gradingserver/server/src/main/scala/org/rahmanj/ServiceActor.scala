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

case class ClientDeleteSession() // TODO, find better place for this

/**
 * 
 */
class ServiceActor extends Actor with ServiceRoutes {
  
  val appserverHostname = Settings(system).AppServer.Hostname
  val appserverPort = Settings(system).AppServer.Port
  
  def authenticatorFactory(token: SessionToken): (RequestContext => Future[Authentication[LoginSession]]) = {
    DeviseAuthenticator(appserverHostname, appserverPort, token)
  }
  
  val sessionRouter = actorRefFactory.actorOf(SessionRoutingActor.props(new DummyContainerFactory()))
  
  // The HTTP Service trait only requires this abstract member
  def actorRefFactory = context

  // This actor only runs routes for the service
  def receive = runRoute(serviceRoute)
}


