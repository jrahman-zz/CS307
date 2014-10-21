package org.rahmanj.messages

import org.rahmanj.sessions.LoginSession
import spray.routing.RequestContext

case class CreateSession(
  ctx: RequestContext,
  login: LoginSession,
  levelInfo: ClientCreateSession
)
