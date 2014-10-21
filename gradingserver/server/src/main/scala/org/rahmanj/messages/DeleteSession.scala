package org.rahmanj.messages

import org.rahmanj.sessions.{LoginSession, SessionToken}
import spray.routing.RequestContext

case class DeleteSession(
  ctx: RequestContext,
  login: LoginSession,
  token: SessionToken
)