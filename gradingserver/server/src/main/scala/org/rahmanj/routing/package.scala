package org.rahmanj

import org.rahmanj.session._
import akka.actor.ActorRef

package object routing {
  type RouteSource = Tuple2[LoginSession, SessionToken]
  type RouteDestination = ActorRef
}
