package org.rahmanj

import org.rahmanj.sessions._
import akka.actor.ActorRef

package object routing {
  type RouteSource = SessionToken
  type RouteDestination = ActorRef
}
