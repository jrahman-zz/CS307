package org.rahmanj.gameplay

import spray.json._

case class ClientLevelSubmission(
  code: String
)

object ClientLevelSubmissionProtocol extends DefaultJsonProtocol {
  implicit val clientLevelSubmissionFormat = jsonFormat1(ClientLevelSubmission)
}

case class ExecutorLevelSubmission(
  code: String
)

object ExecutorLevelSubmissionProtocol extends DefaultJsonProtocol {
  implicit val executorLevelSubmissionFormat = jsonFormat1(ExecutorLevelSubmission)
}
