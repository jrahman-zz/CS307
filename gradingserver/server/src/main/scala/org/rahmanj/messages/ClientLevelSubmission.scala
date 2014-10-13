package org.rahmanj.messages

import spray.json._

case class ClientLevelSubmission(
  code: String
)

object ClientLevelSubmissionProtocol extends DefaultJsonProtocol {
  implicit val clientLevelSubmissionFormat = jsonFormat1(ClientLevelSubmission)
}