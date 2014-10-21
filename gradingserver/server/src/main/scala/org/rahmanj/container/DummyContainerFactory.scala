package org.rahmanj.container

import scala.concurrent.{Future, Promise}
import scala.concurrent.ExecutionContext.Implicits.global
import scala.util.Failure

import spray.httpx.unmarshalling._

import org.rahmanj.messages.{ExecutorResponse, ExecutorRequest, ExecutorLevelResult}

/** [[ContainerFactory]] to create [[DummyContainer]] instances for testing
 * 
 */
class DummyContainerFactory extends ContainerFactory {
  
  def apply(config: ContainerConfig): Future[Option[Container]] = {
    Future {
      Some(new DummyContainer())
    }
  }
  
  private class DummyContainer() extends Container {
    
    def sendMessage[A <: ExecutorRequest](message: A)(implicit f: Unmarshaller[message.Response]): Future[message.Response] = {
      
      // TODO, case statement with dummy results
      
      val p = Promise[message.Response]
      p.future
    }
    
    def ping(): Future[Boolean] = {
      Future {
        true // We're very optimistic
      }
    }
    
    def shutdown() = {
        // NOOP
    }
  }
}