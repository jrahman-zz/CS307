package org.rahmanj.container

// TODO, fill this in
abstract class ContainerConfig()

case class ProcessContainerConfig(port: Int) extends ContainerConfig
case class DockerContainerConfig() extends ContainerConfig