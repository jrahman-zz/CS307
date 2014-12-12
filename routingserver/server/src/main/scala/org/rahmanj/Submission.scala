package org.rahmanj

import spray.routing.RequestContext

import messages.Request

case class Submission(
  ctx: RequestContext,
  submission: Request
)
