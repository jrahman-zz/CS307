package org.rahmanj

import akka.actor._
import akka.event.Logging
import akka.pattern.ask
import akka.util.Timeout
import akka.io.IO

import scala.concurrent.Future
import scala.concurrent.duration._

import spray.can.Http
import spray.http._
import spray.routing.RequestContext
import HttpMethods._
import StatusCodes._

import scala.concurrent.ExecutionContext.Implicits.global

case class Submission(ctx: RequestContext, code: String)
case class Result(ctx: RequestContext, result: Any)
case class Ping(success: Boolean)

case class SubmissionSuccess(res: String) // TODO, create proper type for res
case class SubmissionFailure(res: String) // TODO, create proper type for res

class SessionActor(language: Any, hostname: String, port: Int) extends Actor {
  
  implicit val system = ActorSystem()
  
  val logger = Logging(context.system, this)
  
  // Start in the initial state to receive a submission
  def receive: Receive = receivePing orElse receiveSubmission
  
  def receiveResult: Receive = {
    case Result(ctx, result) =>
      result match {
        case SubmissionSuccess(res) =>
          "Send to database, then send to client (Or otherway?)"
        case SubmissionFailure(res) =>
          "Send error to user, then add submission to database"
      }
      context.become(receiveSubmission orElse receivePing)
    case _ =>
      logger.warning("Warning, receiveResult matched unknown")
      "TODO, error"
  }
  
  def receiveSubmission: Receive = {
    case Submission(ctx, code) =>
      sendSubmission(code) // TODO, create a closure over self
      context.become(receivePing orElse receiveResult)
    case _ =>
      "TODO, error condition"
  }
  
  def receivePing: Receive = {
    case Ping(result) =>
      
      result match {
        case true =>
          logger.debug("Successful ping received")
          schedulePing
          
        case false =>
          logger.debug("Ping failed")
          // TODO, scram, fail hard
      }
  }
  
  def schedulePing() {
    val hostname = this.hostname
    val port = this.port

    val interval = Settings(system).Container.PingInterval seconds
    implicit val timeout: Timeout = Timeout(interval)
    
    system.scheduler.scheduleOnce(interval) {
      val uri = Uri("http://" + hostname + ":" + port + "/ping")
      
      val response = (IO(Http) ? HttpRequest(GET, uri)).mapTo[HttpResponse] map {
        response => response.status match {
          case Success(_) => self ! Ping(true)
          case _ => self ! Ping(false)
        }
      } recover {
        case _ => self ! Ping(false)
      }
    }
  }
  
  def sendSubmission(code: String) = {
    
    
  }
}
