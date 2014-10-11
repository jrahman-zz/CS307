package org.rahmanj.gameplay

import spray.json._

case class ClientLevelResult(
  success: Boolean,
  feedback: String,
  movelist: List[Move]
)

object ClientLevelResultProtocol extends DefaultJsonProtocol {
  implicit val clientLevelResultFormat = jsonFormat2(ClientLevelResult)
}

case class ExecutorLevelResult(
  success: Boolean,
  feedback: String,
  time: Double,
  movelist: List[Move]
)

object ExecutorLevelResultProtocol extends DefaultJsonProtocol {
  import moveFormat._
  implicit val executorLevelResultFormat = jsonFormat4(ExecutorLevelResult)
}
