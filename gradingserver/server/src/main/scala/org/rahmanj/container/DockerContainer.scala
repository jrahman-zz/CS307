package org.rahmanj.container

import scala.concurrent.Future
import scala.concurrent.ExecutionContext.Implicits.global

import tugboat.Client

object DockerContainer {
  
  def apply(config: ContainerConfig) = {
    val client = tugboat.Client()
    for {
      container <- client.containers.create("TODO, container name here from config").volumes("TODO, volumes from config")()
      run       <- client.containers.get(container.id).start.bind(
                  tugboat.Port.Tcp(8080), tugboat.PortBinding.local(8080)
                )()
      info   <- client.containers.get(container.id)()
    } yield info.networkSettings match {
        case Some(networkSettings) => new DockerContainer(networkSettings.ipAddr, 8080)
        case None => // TODO
    }
  }
  
  class DockerContainer(hostname: String, port: Int) extends Container {
    def sendMessage[T](message: T): Future[Any]
    def ping(): Future[Boolean]
  }
}
