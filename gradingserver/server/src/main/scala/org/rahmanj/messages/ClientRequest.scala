package org.rahmanj.messages

import spray.json._

sealed trait ClientRequest

case class ClientCreateSession(
  levelID: Int,
  classID: Int,
  language: Int // TOOD, add type for this
) extends ClientRequest

object ClientCreateSessionProtocol extends DefaultJsonProtocol {
  implicit val clientCreateSessionFormat = jsonFormat3(ClientCreateSession)
}

case class ClientChallengeSubmission(
  code: String
) extends ClientRequest

object ClientChallengeSubmissionProtocol extends DefaultJsonProtocol {
  implicit val clientChallengeSubmissionFormat = jsonFormat1(ClientChallengeSubmission)
}

case class ClientLevelSubmission(
  code: String
) extends ClientRequest 

object ClientLevelSubmissionProtocol extends DefaultJsonProtocol {
  implicit val clientLevelSubmissionFormat = jsonFormat1(ClientLevelSubmission)
}