package org.rahmanj.messages

import spray.json._

case class ClientCreateSession(
  levelID: Int,
  classID: Int,
  language: Int // TOOD, add type for this
) extends ClientRequest

object ClientCreateSessionProtocol extends DefaultJsonProtocol {
  implicit val clientCreateSessionFormat = jsonFormat3(ClientCreateSession)
}