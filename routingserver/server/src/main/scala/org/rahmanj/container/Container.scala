package org.rahmanj.container

import scala.concurrent.Future

import spray.httpx._
import unmarshalling._
import marshalling._

import org.rahmanj.messages.{Response, Request}

/** Represents an generic execution container
 * 
 * @required sendMessage Send a command message to the container
 * @required ping Send a health check to the container
 * @required shutdown Terminate the container
 */
trait Container {
  
  /**
   * @param message The message to be sent to the container
   * @returns [[scala.concurrent.Future]] containing the Response
   */
  def sendMessage[A <: Request](message: A, endpoint: String)(implicit f: Unmarshaller[A#ResponseType], p: Marshaller[A]): Future[A#ResponseType]
  
  /** Checks the health of the container
   * @returns [[scala.concurrent.Future]] containing a [[Boolean]] indicating the outcome
   */
  def ping(): Future[Boolean]
  
  /** 
   * Shut the container down
   */
  def shutdown()

}
