package org.rahmanj.sessions

import akka.actor.ActorRef

/** Represents a given level within the session
 * @constructor create a new [[LevelSession]] instance
 * @param token The [[SessionToken]] this [[LevelSession]] is associated with
 * @param levelID The ID of the level this [[LevelSession]] is associated with
 * @param classID  The ID of the class this [[LevelSession]] is associated with
 * @param sessionActor The [[org.rahmanj.SessionActor]] this [[LevelSession]] is associated with
 * @param lastAccessed
 * @param language
 */
case class LevelSession(
  token: SessionToken,
  levelID: Int,
  classID: Int,
  sessionActor: ActorRef,
  lastAccessed: Any, // TODO, add datetime type
  language: Any)


