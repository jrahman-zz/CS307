package org.rahmanj.messages

import spray.json._

case class ClientChallengeSubmission(
  code: String
) extends ClientRequest

object ClientChallengeSubmissionProtocol extends DefaultJsonProtocol {
  implicit val clientChallengeSubmissionFormat = jsonFormat1(ClientChallengeSubmission)
}