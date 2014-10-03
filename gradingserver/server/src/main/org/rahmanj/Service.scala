package org.rahma`nj

import akka.actor._
import scala.concurrent.ExecutionContext.Implicits.global
import spray.routing._
import directives.CompletionMagnet
import spray.http._


// Separate the route structure from the actual actor
class ServiceActor extends Action with Service {
	
	// The HTTP Service trait only requires this abstract member
	def actorRefFactory = context

	// This actor only runs routes for the service
	def receive = runRoute(serviceRoute)
}


case class DeadContainer(id: Int)

case class Submission(id: Int, reqCtx: RequestContext)

case class PollTimeout()

case class ClientMessage()

case class ReclaimContainer()

class CometActor extends Actor {

	def recieve = {
		case DeadContainer(id) => // TODO
		case Submission() => // TODO
		case PollTimeout() => // TODO
		case ClientMessage() => // TODO
		case ReclaimContainer() => // TODO
	}
}

trait Service extends HttpService {
	
	val cometActor = actorRefFactory.actorOf(Props[CometActor])

	val route = 
		path("") {
			get {

			}
		} ~
		path("submission") {
			post {
				cometActor ! Submission(0, _)
			}
		}
		path("session") {
			post {
				// TODO
			}
			get {
				// TODO
			}	
		}
}
