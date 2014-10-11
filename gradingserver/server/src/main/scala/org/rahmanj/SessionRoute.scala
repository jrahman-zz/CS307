package org.rahmanj

import session.{LoginSession,LevelSession}

case class SessionRoute(
  src: (LoginSession, String),
  dest: LevelSession)