package org.rahmanj

import spray.routing.RequestContext
import session._

case class Routable[T] (
  ctx: RequestContext,
  login: LoginSession,
  token: SessionToken,
  payload: T
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
