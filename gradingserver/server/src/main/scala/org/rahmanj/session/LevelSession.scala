package org.rahmanj.session

import akka.actor.ActorRef

case class LevelSession(
  token: SessionToken,
  levelID: Int,
  classID: Int,
  sessionActor: ActorRef,
  lastAccessed: Any, // TODO, add datetime type
  language: Any)


