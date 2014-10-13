package org.rahmanj.messages

import spray.json._

case class ExecutorCreateSession(
  level: ExecutorLevel
)

object ExecutorCreateSessionProtocol extends DefaultJsonProtocol {
  implicit val executorCreateSessionFormat = jsonFormat1(ExecutorCreateSession)
}
