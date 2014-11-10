package org.rahmanj.messages

import spray.json._

sealed trait Request {
  type ResponseType <: Response
}

/*
 * Opaque to the routing server
 */
case class SessionCreateRequest(
  levelJson: String
) extends Request {
  type ResponseType = SessionCreateResponse
}

case class SessionResetRequest() extends Request {
  type ResponseType = SessionResetResponse
}

case class SessionDeleteRequest() extends Request {
  type RepsonseType = SessionDeleteResponse
}


/*
 * Likely will fill this out more later
 */
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


