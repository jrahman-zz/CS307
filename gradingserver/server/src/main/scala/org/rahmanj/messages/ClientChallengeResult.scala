package org.rahmanj.messages

import spray.json._

case class ClientChallengeResult(
  success: Boolean,
  feedback: String
) extends ClientResponse

object ClientChallengeResultProtocol extends DefaultJsonProtocol {
  implicit val clientChallengeResultFormat = jsonFormat2(ClientChallengeResult)
}
