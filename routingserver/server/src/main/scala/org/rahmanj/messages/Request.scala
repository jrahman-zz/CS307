package org.rahmanj.messages

import spray.httpx._
import marshalling._
import unmarshalling._

import spray.http._
import MediaTypes._

import spray.json._

sealed trait Request {
  type ResponseType <: Response
}

/*
 * Opaque to the routing server
 */
case class SessionCreateRequest(
  levelJson: String
) extends Request {
  type ResponseType = SessionCreateResponse
}

object SessionCreateRequest {
  
  implicit val SessionCreateRequestMarshaller =
    Marshaller.of[SessionCreateRequest](`application/json`) { (value, contentType, ctx) =>
      ctx.marshalTo(HttpEntity(contentType, value.levelJson))
    }
}

case class SessionResetRequest() extends Request {
  type ResponseType = SessionResetResponse
}

case class SessionDeleteRequest() extends Request {
  type RepsonseType = SessionDeleteResponse
}


/*
 * Likely will fill this out more later
 */
case class ChallengeSubmissionRequest(
  code: String,
  timeout: Double
) extends Request {
  type ResponseType = ChallengeResultResponse
}

object ChallengeSubmissionRequestProtocol extends DefaultJsonProtocol {
  implicit val challengeSubmissionRequestFormat = jsonFormat2(ChallengeSubmissionRequest)
  
  implicit val ChallengeSubmissionRequestMarshaller = 
    Marshaller.of[ChallengeSubmissionRequest](`application/json`) { (value, contentType, ctx) =>
      ctx.marshalTo(HttpEntity(contentType, CompactPrinter(value.toJson)))
    }
}

case class LevelSubmissionRequest(
  codelines: String
) extends Request {
  type ResponseType = LevelResultResponse
}

object LevelSubmissionRequestProtocol extends DefaultJsonProtocol {
  implicit val levelSubmissionRequestFormat = jsonFormat1(LevelSubmissionRequest)
  
  implicit val LevelSubmissionRequestMarshaller = 
    Marshaller.of[LevelSubmissionRequest](`application/json`) { (value, contentType, ctx) =>
      ctx.marshalTo(HttpEntity(contentType, CompactPrinter(value.toJson)))
    }
}


