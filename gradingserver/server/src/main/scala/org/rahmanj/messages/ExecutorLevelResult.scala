package org.rahmanj.messages

import spray.json._

case class ExecutorLevelResult(
  success: Boolean,
  feedback: String,
  time: Double,
  movelist: List[Move]
) extends ExecutorResponse

object ExecutorLevelResultProtocol extends DefaultJsonProtocol {
  import MoveProtocol._
  implicit val executorLevelResultFormat = jsonFormat4(ExecutorLevelResult)
}
