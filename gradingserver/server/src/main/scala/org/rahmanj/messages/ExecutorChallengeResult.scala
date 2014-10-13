package org.rahmanj.messages

import spray.json._

case class ExecutorChallengeResult(
  success: Boolean,
  feedback: String,
  time: Double
)

object ExecutorChallengeResultProtocol extends DefaultJsonProtocol {
  implicit val executorChallengeResultFormat = jsonFormat3(ExecutorChallengeResult)
}