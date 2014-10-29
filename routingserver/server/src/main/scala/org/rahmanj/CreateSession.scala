package org.rahmanj

import spray.routing.RequestContext

import messages.SessionCreateRequest
import sessions.SessionToken

case class CreateSession(ctx: RequestContext, loginSession: SessionToken, request: SessionCreateRequest)
