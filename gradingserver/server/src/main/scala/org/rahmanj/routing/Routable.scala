package org.rahmanj.routing

import spray.routing.RequestContext
import org.rahmanj.session._

case class Routable (
  ctx: RequestContext,
  login: LoginSession,
  token: SessionToken,
  payload: Any
)

//case class UnroutedLevelSubmission(
//  ctx: RequestContext,
//  login: LoginSession,
//  token: SessionToken,
//  code: String) extends Routable
//  
//case class UnroutedChallengeSubmission(
//  ctx: RequestContext,
//  login: LoginSession,
//  token: SessionToken,
//  code: String) extends Routable
//  
//case class UnroutedResetLevel(
//  ctx: RequestContext,
//  login: LoginSession,
//  token: SessionToken) extends Routable
//  
//case class UnroutedDeleteSession(
//  ctx: RequestContext,
//  login: LoginSession,
//  token: SessionToken) extends Routable
