package org.rahmanj

import akka.actor._
import com.typesafe.config._

class Settings(config: Config, extendedSystem: ExtendedActorSystem) extends Extension {
  object Http {
    val Port = config.getInt("server.http.port")
    val Interface = config.getString("server.http.interface")
  }
  
  object Container {
    val PingInterval = config.getDouble("server.container.ping-interval")
  }
}

object Settings extends ExtensionId[Settings] with ExtensionIdProvider {
  override def lookup = Settings
  override def createExtension(system: ExtendedActorSystem) =
    new Settings(system.settings.config, system)
  
  def apply(context: ActorContext): Settings = apply(context.system)
}
