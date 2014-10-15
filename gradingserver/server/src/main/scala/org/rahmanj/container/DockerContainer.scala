package org.rahmanj.container

import akka.actor.ActorSystem

import scala.concurrent.Future
import scala.concurrent.ExecutionContext.Implicits.global

import tugboat.Client

import org.rahmanj.messages.{ExecutorResponse, ExecutorRequest}
import org.rahmanj.Settings

object DockerContainer {
  
  implicit val system = ActorSystem()
  
  def apply(config: ContainerConfig): Future[Option[Container]] = {
    val client = tugboat.Client()
    for {
      container <- client.containers.create("TODO, container name here from config").volumes("TODO, volumes from config")()
      run       <- client.containers.get(container.id).start.bind(
                  tugboat.Port.Tcp(Settings(system).Container.HostBindPort),
                  tugboat.PortBinding.local(Settings(system).Container.ContainerBindPort)
                )()
      info   <- client.containers.get(container.id)()
    } yield info match {
        case Some(settings) => Some(new DockerContainer(settings.networkSettings.ipAddr, 8080))
        case None => None
    }
  }
  
  private class DockerContainer(hostname: String, port: Int) extends Container {
    def sendMessage[Req <: ExecutorRequest](message: Req): Future[message.Response]
    def ping(): Future[Boolean]
  }
}
