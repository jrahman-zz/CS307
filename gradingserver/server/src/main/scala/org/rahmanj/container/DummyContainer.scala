package org.rahmanj.container

import scala.concurrent.Future
import scala.concurrent.ExecutionContext.Implicits.global

import org.rahmanj.messages.{ExecutorResponse, ExecutorRequest, ExecutorLevelResult}

object DummyContainer {
  
  def apply(config: ContainerConfig): Future[Option[Container]] = {
    Future {
      Some(new DummyContainer())
    }
  }
  
  private class DummyContainer() extends Container {
    def sendMessage[Req <: ExecutorRequest](message: Req): Future[message.Response] = {
      Future {
        new ExecutorResponse {}
      }
    }
    def ping(): Future[Boolean] = {
      Future {
        true // We're very optimistic
      }
    }
  }
}