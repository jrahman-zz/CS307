package org.rahmanj.messages

import spray.json._

case class ClientCreateSession(
  levelID: Int,
  classID: Int,
  language: Int // TOOD, add type for this
)

object ClientCreateSessionProtocol extends DefaultJsonProtocol {
  implicit val clientCreateSessionFormat = jsonFormat3(ClientCreateSession)
}