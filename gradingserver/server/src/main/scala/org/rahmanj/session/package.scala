package org.rahmanj

package object session {
  type SessionToken = String
  
  case class Python {
    val containerName = "PythonContainer"
  }
}
