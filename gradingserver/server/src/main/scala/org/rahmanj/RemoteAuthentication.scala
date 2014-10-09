package org.rahmanj

import spray.routing.RequestContext
import scala.concurrent.{Future,future}
import scala.concurrent.ExecutionContext.Implicits.global

package object rahmanj {
  
  def RemoteAuthenticator(ctx: RequestContext): Future[Boolean] = {
    // TODO
    future {
      true
    }
  }
  
}
