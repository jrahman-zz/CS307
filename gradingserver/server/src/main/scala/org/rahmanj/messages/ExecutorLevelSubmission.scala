package org.rahmanj.messages

import spray.json._

case class ExecutorLevelSubmission(
  code: String
)

object ExecutorLevelSubmissionProtocol extends DefaultJsonProtocol {
  implicit val executorLevelSubmissionFormat = jsonFormat1(ExecutorLevelSubmission)
}
