package org.rahmanj.messages

import spray.json._

sealed trait Request {
  type ResponseType <: Response
}

case class SessionCreateRequest(
  level: Level
) extends Request {
  type ResponseType = SessionCreateResponse
}

object SessionCreateRequestProtocol extends DefaultJsonProtocol {
  import LevelProtocol._
  implicit val sessionCreateRequestFormat = jsonFormat1(SessionCreateRequest)
}

case class SessionResetRequest()

object SessionResetRequestProtocol extends DefaultJsonProtocol {
  implicit val sessionResetRequestFormat = jsonFormat0(SessionResetRequest)
}

case class SessionDeleteRequest()

object SessionDeleteRequestProtocol extends DefaultJsonProtocol {
  implicit val sessionDeleteRequestFormat = jsonFormat0(SessionDeleteRequest)
}

case class ChallengeSubmissionRequest(
  code: String,
  timeout: Double
) extends Request {
  type ResponseType = ChallengeResultResponse
}

object ChallengeSubmissionRequestProtocol extends DefaultJsonProtocol {
  implicit val challengeSubmissionRequestFormat = jsonFormat2(ChallengeSubmissionRequest)
}

case class LevelSubmissionRequest(
  code: String
) extends Request {
  type ResponseType = LevelResultResponse
}

object LevelSubmissionRequestProtocol extends DefaultJsonProtocol {
  implicit val levelSubmissionRequestFormat = jsonFormat1(LevelSubmissionRequest)
}


