package org.rahmanj.messages

import spray.json._

case class Move(timestep: Int)

object MoveProtocol extends DefaultJsonProtocol {
  implicit val moveFormat = jsonFormat1(Move)
}
