package org.rahmanj.container

import scala.concurrent.Future

import org.rahmanj.messages.{ExecutorResponse, ExecutorRequest}

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
  def sendMessage[Req <: ExecutorRequest](message: Req): Future[message.Response]
  
  /** Checks the health of the container
   * @returns [[scala.concurrent.Future]] containing a [[Boolean]] indicating the outcome
   */
  def ping(): Future[Boolean]
  
  /** Shuts the container down
   * @returns [[scala.concurrent.Future]] containing a [[Boolean]] indicating the outcome
   */
  def shutdown(): Future[Boolean]
  // TODO, extend interface as needed
}

