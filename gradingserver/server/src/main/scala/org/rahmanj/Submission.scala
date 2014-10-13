package org.rahmanj

import spray.routing.RequestContext

case class Submission(
  ctx: RequestContext,
  submission: Any
)
