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
    
    object Python {
      val ContainerPath = config.getString("server.container.python.container-path")
      val ExecutorName  = config.getString("server.container.python.executor-name")
    }
  }
  
  object Langauge {
    object Python {
      val ContainerName   = config.getString("server.language.python.container-name")
    }
  }
}

object Settings extends ExtensionId[Settings] with ExtensionIdProvider {
  override def lookup = Settings
  override def createExtension(system: ExtendedActorSystem) =
    new Settings(system.settings.config, system)
  
  def apply(context: ActorContext): Settings = apply(context.system)
}
