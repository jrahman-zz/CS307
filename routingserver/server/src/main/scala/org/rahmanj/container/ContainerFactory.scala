package org.rahmanj.container

import scala.concurrent.Future

trait ContainerFactory {
  def apply(config: ContainerConfig): Future[Option[Container]]
}
