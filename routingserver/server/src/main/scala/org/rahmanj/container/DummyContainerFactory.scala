package org.rahmanj.container

import scala.concurrent.{Future, Promise}
import scala.concurrent.ExecutionContext.Implicits.global
import scala.util.Failure

import spray.httpx._
import unmarshalling._
import marshalling._

import org.rahmanj.messages.{Response, Request, LevelResultResponse}

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
    
    def sendMessage[A <: Request](message: A, endpoint: String)(implicit f: Unmarshaller[A#ResponseType], p: Marshaller[A]): Future[A#ResponseType] = {
      
      // TODO, case statement with dummy results
      
      val p = Promise[message.ResponseType]
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