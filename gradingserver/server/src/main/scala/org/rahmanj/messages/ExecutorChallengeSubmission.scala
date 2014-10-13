package org.rahmanj.messages

import spray.json._

case class ExecutorChallengeSubmission(
  code: String,
  timeout: Double
)

object ExecutorChallengeSubmissionProtocol extends DefaultJsonProtocol {
  implicit val executorChallengeSubmissionFormat = jsonFormat2(ExecutorChallengeSubmission)
}
