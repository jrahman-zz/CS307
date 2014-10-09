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

import com.github.mauricio.async.db.mysql.MySQLConnection
import com.github.mauricio.async.db.{Connection,Configuration}

import scala.concurrent.ExecutionContext.Implicits.global

case class Submission(ctx: RequestContext, code: String)
case class Result(ctx: RequestContext, result: Any)
case class Ping(success: Boolean)

case class SubmissionSuccess(res: String) // TODO, create proper type for res
case class SubmissionFailure(res: String) // TODO, create proper type for res

class SessionActor(language: Any, hostname: String, port: Int) extends Actor with ActorLogging {
  
  implicit val system = ActorSystem()
  
  // Start in the initial state to receive a submission
  def receive: Receive = receiveSubmission orElse receiveCommon
  
  def receivePing: Receive = {
    case Ping(result) =>
      result match {
        case true =>
          log.debug("Successful ping received")
          schedulePing
        case false =>
          log.debug("Ping failed")
          // TODO, scram, fail hard
      }
  }
  
  def receiveUnknown: Receive = {
    case _ => log.warning("Known message received by actor")
  }
  
  def receiveCommon = receivePing orElse receiveUnknown
  
  def receiveResult: Receive = {
    case Result(ctx, result) =>
      result match {
        case SubmissionSuccess(res) =>
          ctx.complete(saveResult(res))
        case SubmissionFailure(res) =>
          "Send error to user, then add submission to database"
      }
      context.become(receiveSubmission orElse receiveCommon)
  }
  
  def receiveSubmission: Receive = {
    case Submission(ctx, code) =>
      sendSubmission(code) // TODO, create a closure over self
      context.become(receiveResult orElse receiveCommon)
  }
  
  def schedulePing() {
    val hostname = this.hostname
    val port = this.port

    val interval = Settings(system).Container.PingInterval seconds
    implicit val timeout: Timeout = Timeout(interval)
    
    system.scheduler.scheduleOnce(interval) {
      
      val response = (IO(Http) ? HttpRequest(GET, getUri)).mapTo[HttpResponse] map {
        response => response.status match {
          case Success(_) => self ! Ping(true)
          case _ => self ! Ping(false)
        }
      } recover {
        case _ => self ! Ping(false)
      }
    }
  }
  
  def sendSubmission(code: String): Future[HttpResponse] = {
    // TODO, send submission to container
    Future {
      HttpResponse()
    }
  }
  
  // TODO, define correct return type
  def saveResult(result: Any): Future[String] = {
    // TODO, store result into database
    Future {
      "TODO"
    }
  }
  
  def getDatabaseConnection: Future[Connection] = {
    val configuration = Configuration(Settings(system).Database.Username)
    val connection = new MySQLConnection(configuration)
    connection.connect
  }
  
  def getUri(): Uri = {
    Uri("http://" + hostname + ":" + port + "/ping")
  }
}
