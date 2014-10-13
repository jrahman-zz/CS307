package org.rahmanj.messages

import spray.json._

case class ClientChallengeResult(
  success: Boolean,
  feedback: String
)

object ClientChallengeResultProtocol extends DefaultJsonProtocol {
  implicit val clientChallengeResultFormat = jsonFormat2(ClientChallengeResult)
}
