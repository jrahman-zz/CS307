package org.rahmanj.messages

import spray.json._

case class ExecutorSessionCreated(
  success: Boolean
) extends ExecutorResponse

object ExecutorSessionCreatedProtocol extends DefaultJsonProtocol {
  implicit val executorSessionCreatedFormat = jsonFormat1(ExecutorSessionCreated)
}
