name := "gradingserver"

version := "SNAPSHOT"

scalaVersion := "2.10.3"

libraryDependencies ++= Seq(
    "com.typesafe.akka" %% "akka-actor" % "2.3.6"
)

libraryDependencies ++= Seq(
    "io.spray" % "spray-can" % "1.3.1",
    "io.spray" % "spray-routing" % "1.3.1",
    "io.spray" % "spray-client" % "1.3.1"
)

libraryDependencies += "com.typesafe" % "config" % "1.2.0"

libraryDependencies ++= Seq(
    "org.slf4j" % "slf4j-api" % "1.7.7",
    "org.slf4j" % "slf4j-simple" % "1.7.7"
)

libraryDependencies += "com.github.mauricio" %% "mysql-async" % "0.2.15"

libraryDepenencies += "" %% "reactive-docker" % ""

