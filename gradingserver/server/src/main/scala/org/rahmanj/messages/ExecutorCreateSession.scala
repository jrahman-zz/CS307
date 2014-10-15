package org.rahmanj.messages

import spray.json._

case class ExecutorCreateSession(
  level: ExecutorLevel
) extends ExecutorRequest {
  type Response = ExecutorSessionCreated
}

object ExecutorCreateSessionProtocol extends DefaultJsonProtocol {
  import ExecutorLevelProtocol._
  implicit val executorCreateSessionFormat = jsonFormat1(ExecutorCreateSession)
}
