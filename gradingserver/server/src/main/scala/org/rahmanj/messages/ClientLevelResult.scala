package org.rahmanj.messages

import spray.json._

case class ClientLevelResult(
  success: Boolean,
  feedback: String,
  movelist: List[Move]
)

object ClientLevelResultProtocol extends DefaultJsonProtocol {
  implicit val clientLevelResultFormat = jsonFormat2(ClientLevelResult)
}