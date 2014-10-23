package org.rahmanj.messages

import spray.json._

import org.rahmanj.sessions.SessionToken

sealed trait Response

case class SessionCreateResponse(
  success: Boolean,
  sessionID: SessionToken
) extends Response

object SessionCreateResponseProtocol extends DefaultJsonProtocol {
  implicit val sessionCreateResponseFormat = jsonFormat2(SessionCreateResponse)
}

case class ChallengeResultResponse(
  success: Boolean,
  feedback: String,
  time: Double
) extends Response

object ChallengeResultResponseProtocol extends DefaultJsonProtocol {
  implicit val challengeResultResponseFormat = jsonFormat3(ChallengeResultResponse)
}

case class LevelResultResponse(
  success: Boolean,
  feedback: String,
  time: Double,
  movelist: List[Move]
) extends Response

object LevelResultResponseProtocol extends DefaultJsonProtocol {
  import MoveProtocol._
  implicit val levelResultResponseFormat = jsonFormat4(LevelResultResponse)
}
