package org.rahmanj.messages

import spray.json._

sealed trait ExecutorRequest {
  type Response <: ExecutorResponse
}

case class ExecutorCreateSession(
  level: ExecutorLevel
) extends ExecutorRequest {
  type Response = ExecutorSessionCreated
}

object ExecutorCreateSessionProtocol extends DefaultJsonProtocol {
  import ExecutorLevelProtocol._
  implicit val executorCreateSessionFormat = jsonFormat1(ExecutorCreateSession)
}


case class ExecutorChallengeSubmission(
  code: String,
  timeout: Double
) extends ExecutorRequest {
  type Response = ExecutorChallengeResult
}

object ExecutorChallengeSubmissionProtocol extends DefaultJsonProtocol {
  implicit val executorChallengeSubmissionFormat = jsonFormat2(ExecutorChallengeSubmission)
}

case class ExecutorLevelSubmission(
  code: String
) extends ExecutorRequest {
  type Response = ExecutorLevelResult
}

object ExecutorLevelSubmissionProtocol extends DefaultJsonProtocol {
  implicit val executorLevelSubmissionFormat = jsonFormat1(ExecutorLevelSubmission)
}


