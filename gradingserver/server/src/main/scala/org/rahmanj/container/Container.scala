package org.rahmanj.container

import scala.concurrent.Future

import org.rahmanj.messages.{ExecutorResponse, ExecutorRequest}

trait Container {
  def sendMessage[Req <: ExecutorRequest](message: Req): Future[message.Response]
  def ping(): Future[Boolean]
  // TODO, extend interface as needed
}

