package org.rahmanj

import akka.actor._
import com.typesafe.config._

class Settings(config: Config, extendedSystem: ExtendedActorSystem) extends Extension {
  object Http {
    val Port = config.getInt("server.http.port")
    val Interface = config.getString("server.http.interface")
  }
  
  object Container {
    val PingInterval      = config.getDouble("server.container.ping-interval")
    val ContainerBindPort = config.getInt("server.container.container-bind-port")
    val HostBindPort      = config.getInt("server.container.host-bind-port")
  }
  
  object Langauge {
    object Python {
      val ContainerName   = config.getString("server.language.python.container-name")
    }
  }
  
  object Database {
    val Username = config.getString("server.database.username")
    val Password = config.getString("server.database.password")
    val Hostname = config.getString("server.database.hostname")
    val Port     = config.getInt("server.database.port")
  }
  
  object AppServer {
    val Hostname = config.getString("server.appserver.hostname")
    val Port = config.getInt("server.appserver.port")
  }
}

object Settings extends ExtensionId[Settings] with ExtensionIdProvider {
  override def lookup = Settings
  override def createExtension(system: ExtendedActorSystem) =
    new Settings(system.settings.config, system)
  
  def apply(context: ActorContext): Settings = apply(context.system)
}
