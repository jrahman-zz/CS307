package org.rahmanj.container

import scala.concurrent.Future

trait Container {
  def sendMessage[T](message: T): Future[Any]
  def ping(): Future[Boolean]
  // TODO, extend interface as needed
}

