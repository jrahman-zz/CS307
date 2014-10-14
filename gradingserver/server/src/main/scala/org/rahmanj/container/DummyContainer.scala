package org.rahmanj.container

import scala.concurrent.Future
import scala.concurrent.ExecutionContext.Implicits.global

object DummyContainer {
  
  def apply(config: ContainerConfig) = {
    Future {
      new DummyContainer()
    }
  }
  
  class DummyContainer() extends Container {
    def sendMessage[T](message: T): Future[Any] = {
      Future {
        "Empty"
      }
    }
    def ping(): Future[Boolean] = {
      Future {
        true // We're very optimistic
      }
    }
  }
}