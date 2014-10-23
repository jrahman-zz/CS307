package org.rahmanj.messages

import spray.json._

case class Level {
  // TODO, define level format,
}

object LevelProtocol extends DefaultJsonProtocol {
  implicit val levelFormat = jsonFormat0(Level)
}
