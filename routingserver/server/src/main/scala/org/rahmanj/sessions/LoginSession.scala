package org.rahmanj.sessions

import com.roundeights.hasher.Implicits._

/**
 * @constructor Creates an new [[LoginSession]] instance
 * @param username The username for the [[LoginSession]]
 * @param token The [[SessionToken]] for this [[LoginSession]]
 */
case class LoginSession(
  username: String,
  token: SessionToken
) {
  def hash() = (username + ":" + token).sha512
}
