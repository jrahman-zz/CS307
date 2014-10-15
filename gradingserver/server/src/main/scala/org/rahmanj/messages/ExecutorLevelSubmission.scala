package org.rahmanj.messages

import spray.json._

case class ExecutorLevelSubmission(
  code: String
) extends ExecutorRequest {
  type Response = ExecutorLevelResult
}

object ExecutorLevelSubmissionProtocol extends DefaultJsonProtocol {
  implicit val executorLevelSubmissionFormat = jsonFormat1(ExecutorLevelSubmission)
}
