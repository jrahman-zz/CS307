package org

import rahmanj.session._

package object rahmanj {
  type RouteSource = (LoginSession, SessionToken)
  type RouteDestination = LevelSession
}
