package org.rahmanj.messages

trait ExecutorRequest {
  type Response <: ExecutorResponse
}
