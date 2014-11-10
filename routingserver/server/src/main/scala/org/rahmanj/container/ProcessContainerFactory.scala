package org.rahmanj.container

import akka.actor.ActorSystem
import akka.util.Timeout
import akka.pattern.ask
import akka.io.IO

import scala.concurrent.{Future, Promise}
import scala.concurrent.ExecutionContext.Implicits.global
import scala.concurrent.duration._

import scala.sys.process._

import spray.can.Http
import spray.http._
import HttpMethods._

import spray.httpx.unmarshalling._
import spray.httpx.ResponseTransformation._
import spray.httpx.SprayJsonSupport

import spray.json._

import org.slf4j.{Logger,LoggerFactory}

import org.rahmanj.messages.{Response, Request}
import org.rahmanj.Settings

/** [[ContainerFactory]] to create [[DockerContainer]] instances
 * 
 */
class ProcessContainerFactory extends ContainerFactory {
  
  implicit val system = ActorSystem()
  
  def apply(config: ContainerConfig): Future[Option[Container]] = {
    
    val executorPath = Settings(system).Container.Python.ContainerPath
    val port = 5000 // Smuggle this in later
    val process = Seq(executorPath, "-p", port.toString) run
    
    Future {
      Some(new ProcessContainer(process, port))
    }
  }
  
  /** [[ProcessContainer]] 
   * 
   * @constructor Create a new instance of the ProcessContainer
   * @param process Process for the given container
   * @param port Port number for the given container
   */
  private class ProcessContainer(process: Process, port: Int) extends Container with SprayJsonSupport {
    
    val logger = LoggerFactory.getLogger(classOf[ProcessContainer])
    val uri = s"http://localhost:$port"
    
    def sendMessage[A <: Request](message: A, endpoint: String)(implicit f: Unmarshaller[A#ResponseType]): Future[A#ResponseType] = {
      
      implicit val timeout = Timeout(60.seconds)
      
      val container_endpoint = s"$uri/$endpoint"
      
      logger.info(s"Sending request to $container_endpoint")
      
      val send = (req: HttpRequest) => (IO(Http) ? req).mapTo[HttpResponse]
      val pipeline = send ~> unmarshal[A#ResponseType]
      pipeline(HttpRequest(GET, Uri(container_endpoint)))
    }
    
    def ping(): Future[Boolean] = {
      implicit val timeout = Timeout(1.seconds)
      
      val endpoint = s"$uri/health"
      
      logger.info(s"Sending pint to $endpoint")
      
      def checkResponse(response: HttpResponse): Boolean = {
        response.status match {
          case StatusCodes.OK => true
          case _ => false
        }
      }
      
      val request = (IO(Http) ? HttpRequest(GET, Uri(endpoint))).mapTo[HttpResponse]
      for {
        response <- request
      } yield (checkResponse(response))
    }
    
    def shutdown() = {
      process.destroy() // No mercy
    }
  }
}