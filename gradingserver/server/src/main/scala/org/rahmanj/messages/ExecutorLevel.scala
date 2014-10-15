package org.rahmanj.messages

import spray.json._

case class ExecutorLevel {
  // TODO, define level format,
}

object ExecutorLevelProtocol extends DefaultJsonProtocol {
  implicit val executorLevelFormat = jsonFormat0(ExecutorLevel)
}
