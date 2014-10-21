package org.rahmanj.messages

import spray.json._

sealed trait ExecutorResponse

case class ExecutorSessionCreated(
  success: Boolean
) extends ExecutorResponse

object ExecutorSessionCreatedProtocol extends DefaultJsonProtocol {
  implicit val executorSessionCreatedFormat = jsonFormat1(ExecutorSessionCreated)
}

case class ExecutorChallengeResult(
  success: Boolean,
  feedback: String,
  time: Double
) extends ExecutorResponse

object ExecutorChallengeResultProtocol extends DefaultJsonProtocol {
  implicit val executorChallengeResultFormat = jsonFormat3(ExecutorChallengeResult)
}

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
