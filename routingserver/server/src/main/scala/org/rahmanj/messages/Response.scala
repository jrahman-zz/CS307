package org.rahmanj.messages

import spray.httpx.unmarshalling._
import spray.httpx.marshalling._
import spray.json._
import spray.util._
import spray.http._
import MediaTypes._

import org.rahmanj.sessions.SessionToken

sealed trait Response

case class SessionCreateResponse(
  success: Boolean,
  sessionID: SessionToken
) extends Response

object SessionCreateResponseProtocol extends DefaultJsonProtocol {
  implicit val sessionCreateResponseFormat = jsonFormat2(SessionCreateResponse)
  
  implicit val SessionCreateResponseMarshaller = 
    Marshaller.of[SessionCreateResponse](`application/json`) { (value, contentType, ctx) =>
      ctx.marshalTo(HttpEntity(contentType, CompactPrinter(value.toJson)))
    }
}

/*
 * Both of these are opaque to the routing server
 */
case class ChallengeResultResponse(
  result: String
) extends Response

object ChallengeResultResponse {
  
  implicit val ChallengeResultResponseUnmarshaller =
    Unmarshaller[ChallengeResultResponse](`application/json`) {
      case HttpEntity.NonEmpty(contentType, data) =>
        ChallengeResultResponse(data.asString)
    }
  
  implicit val ChallengeResultResponseMarshaller = 
    Marshaller.of[ChallengeResultResponse](`application/json`) { (value, contentType, ctx) =>
      ctx.marshalTo(HttpEntity(contentType, value.result))
    }
}

case class LevelResultResponse(
  result: String
) extends Response

object LevelResultResponse {
  implicit val LevelResultResponseUnmarshaller = 
    Unmarshaller[LevelResultResponse](`application/json`) {
      case HttpEntity.NonEmpty(contentType, data) =>
        LevelResultResponse(data.asString)
    }
  
  implicit val LevelResultResponseMarshaller = 
    Marshaller.of[LevelResultResponse](`application/json`) { (value, contentType, ctx) =>
      ctx.marshalTo(HttpEntity(contentType, value.result))
    }
}

case class SessionResetResponse() extends Response

object SessionResetResponse {
  implicit val SessionResetResponseUnmarshaller =
    Unmarshaller[SessionResetResponse](`application/json`) {
      case HttpEntity.NonEmpty(contentType, data) =>
        SessionResetResponse()
    }
}

case class SessionDeleteResponse() extends Response

object SessionDeleteResponse {
  implicit val SessionRDeleteResponseUnmarshaller =
    Unmarshaller[SessionDeleteResponse](`application/json`) {
      case HttpEntity.NonEmpty(contentType, data) =>
        SessionDeleteResponse()
    }
}
