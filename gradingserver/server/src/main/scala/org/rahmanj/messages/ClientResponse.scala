package org.rahmanj.messages

import spray.json._

sealed trait ClientResponse

case class ClientChallengeResult(
  success: Boolean,
  feedback: String
) extends ClientResponse

object ClientChallengeResultProtocol extends DefaultJsonProtocol {
  implicit val clientChallengeResultFormat = jsonFormat2(ClientChallengeResult)
}

case class ClientLevelResult(
  success: Boolean,
  feedback: String,
  movelist: List[Move]
) extends ClientResponse

object ClientLevelResultProtocol extends DefaultJsonProtocol {
  import MoveProtocol._
  implicit val clientLevelResultFormat = jsonFormat3(ClientLevelResult)
}
