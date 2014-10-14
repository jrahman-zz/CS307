package org.rahmanj.messages

import spray.json._

case class Move {

}

object MoveProtocol {
  implicit val moveFormat = jsonFormat0(Move)
}
