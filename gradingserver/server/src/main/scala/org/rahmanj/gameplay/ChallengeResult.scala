package org.rahmanj.gameplay

import spray.json._

case class ClientChallengeResult(
  success: Boolean,
  feedback: String
)

object ClientChallengeResultProtocol extends DefaultJsonProtocol {
  implicit val clientChallengeResultFormat = jsonFormat2(ClientChallengeResult)
}

case class ExecutorChallengeResult(
  success: Boolean,
  feedback: String,
  time: Double
)

object ExecutorChallengeResultProtocol extends DefaultJsonProtocol {
  implicit val executorChallengeResultFormat = jsonFormat3(ExecutorChallengeResult)
}
