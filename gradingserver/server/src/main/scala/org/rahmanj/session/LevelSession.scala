package org.rahmanj.session

case class Python {
  val containerName = "PythonContainer"
}

case class LevelSession(
  token: String,
  levelID: Int,
  classID: Int,
  language: Any)


