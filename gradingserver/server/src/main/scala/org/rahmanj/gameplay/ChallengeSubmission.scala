package org.rahmanj.gameplay

import spray.json._

case class ClientChallengeSubmission(
  code: String
)

object ClientChallengeSubmissionJsonProtocol extends DefaultJsonProtocol {
  implicit val clientChallengeSubmissionFormat = jsonFormat1(ClientChallengeSubmission)
}

case class ExecutorChallengeSubmission(
  code: String,
  timeout: Double
)

object ExecutorChallengeSubmissionProtocol extends DefaultJsonProtocol {
  implicit val executorChallengeSubmissionFormat = jsonFormat2(ExecutorChallengeSubmission)
}
