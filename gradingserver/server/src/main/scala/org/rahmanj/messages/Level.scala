package org.rahmanj.messages

import spray.json._

case class Level(levelId: Int, classId: Int)

object LevelProtocol extends DefaultJsonProtocol {
  implicit val levelFormat = jsonFormat2(Level)
}
