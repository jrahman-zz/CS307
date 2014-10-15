package org.rahmanj.messages

import spray.json._

case class ClientLevelResult(
  success: Boolean,
  feedback: String,
  movelist: List[Move]
)

object ClientLevelResultProtocol extends DefaultJsonProtocol {
  import MoveProtocol._
  implicit val clientLevelResultFormat = jsonFormat3(ClientLevelResult)
}