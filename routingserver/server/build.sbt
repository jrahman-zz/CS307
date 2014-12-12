name := "routingserver"

version := "SNAPSHOT"

scalaVersion := "2.11.2"

resolvers += "Typesafe repository" at "http://repo.typesafe.com/typesafe/releases/"

libraryDependencies ++= Seq(
    "com.typesafe.akka" %% "akka-actor" % "2.3.6"
)

libraryDependencies ++= Seq(
    "io.spray" %% "spray-can" % "1.3.2",
    "io.spray" %% "spray-routing-shapeless2" % "1.3.2",
    "io.spray" %% "spray-client" % "1.3.2",
    "io.spray" %% "spray-json" % "1.3.0"
)

libraryDependencies += "com.typesafe" % "config" % "1.2.0"

libraryDependencies ++= Seq(
    "org.slf4j" % "slf4j-api" % "1.7.7",
    "org.slf4j" % "slf4j-simple" % "1.7.7"
)

resolvers += Resolver.sonatypeRepo("snapshots")

libraryDependencies += "org.almoehi" %% "reactive-docker" % "0.1-SNAPSHOT"

resolvers += "softprops-maven" at "http://dl.bintray.com/content/softprops/maven"

libraryDependencies += "me.lessis" %% "tugboat" % "0.1.0-SNAPSHOT"

resolvers += "RoundEights" at "http://maven.spikemark.net/roundeights"

libraryDependencies += "com.roundeights" %% "hasher" % "1.0.0"

