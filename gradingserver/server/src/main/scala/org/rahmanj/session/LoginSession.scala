package org.rahmanj.session

import com.roundeights.hasher.Implicits._

case class LoginSession(
  username: String,
  token: SessionToken
) {
  def hash() = (username + ":" + token).sha512
}
