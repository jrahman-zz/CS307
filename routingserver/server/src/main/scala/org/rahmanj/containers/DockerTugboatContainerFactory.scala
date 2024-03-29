package org.rahmanj.containers

import akka.actor.ActorSystem
import akka.util.Timeout
import akka.pattern.ask
import akka.io.IO

import scala.concurrent.{Future, Promise}
import scala.concurrent.ExecutionContext.Implicits.global
import scala.concurrent.duration._

import spray.can.Http
import spray.http._
import HttpMethods._

import spray.httpx._
import unmarshalling._
import marshalling._
import SprayJsonSupport._
import spray.client.pipelining._

import spray.json._

import tugboat.Client

import org.slf4j.{Logger,LoggerFactory}

import org.rahmanj.messages.{Response, Request}
import org.rahmanj.Settings

/** [[ContainerFactory]] to create [[DockerContainer]] instances
 * 
 */
class DockerTugboatContainerFactory extends ContainerFactory {

  implicit val system = ActorSystem()
  
  def apply(config: ContainerConfig): Future[Option[Container]] = {
    val client = tugboat.Client()
    for {
      container <- client.containers.create("python")()
      run       <- client.containers.get(container.id).start.bind(
                  tugboat.Port.Tcp(Settings(system).Container.ContainerBindPort),
                  tugboat.PortBinding.local(Settings(system).Container.HostBindPort)
                )()
      info <- client.containers.get(container.id)()
    } yield {
      (info, container) match {
        case (Some(info), c) => Some(
                new DockerContainer(
                    info.networkSettings.ipAddr,
                    Settings(system).Container.HostBindPort,
                    c.id)
                  )
        case (None, c) => None
      }
    }
  }
  
  /** [[DockerContainer]] 
   * 
   * @constructor Create a new instance of the DockerContainer
   * @param hostname Hostname for the given container
   * @param port Port number for the given container
   */
  private class DockerContainer(hostname: String, port: Int, containerID: String) extends Container with SprayJsonSupport {
    
    val logger = LoggerFactory.getLogger(classOf[DockerContainer])
    val uri = "http://" + hostname + ":" + port
    
    def sendMessage[A <: Request](message: A, endpoint: String)(implicit f: Unmarshaller[A#ResponseType], p: Marshaller[A]): Future[A#ResponseType] = {
      
      implicit val timeout = Timeout(60.seconds)
      
      val container_endpoint = uri + s"/$endpoint"
      
      logger.info(s"Sending request to $container_endpoint")
      
      val request = Post(container_endpoint, message)
      val send: HttpRequest => Future[HttpResponse] = (req: HttpRequest) => (IO(Http) ? req).mapTo[HttpResponse]
      val pipeline = send ~> unmarshal[A#ResponseType]
      pipeline(request)
    }
    
    def ping(): Future[Boolean] = {
      implicit val timeout = Timeout(1.seconds)
      
      val endpoint = uri + "/health"
      
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
      val client = tugboat.Client();
      client.containers.get(containerID).stop(1.seconds)()
    }
  }
}
