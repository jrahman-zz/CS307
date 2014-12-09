class SubmissionsController < ApplicationController
  # Allow submissions to be handled asynchronously
  include AsyncController

  ROUTING_SERVER = 'http://klamath.dnsdynamic.com:8089'

  def finish_submission http
    http.callback do
      finish_request do
        puts '\n\n#### Routing Server response captured, returning to client ####\n\n'

        json = JSON.parse http.response

        now = Time.now

        @submission = Submission.find_or_initialize_by(@info)
        # If the submission has just been created, say that the start time is now
        if @submission.new_record?
          @submission.started_at = now
        end

        # If the attempt was successful, store the date of completion
        if json.completed
          @submission.completed_at = now
        end

        @submission.save


        @attempt = Attempt.new
        @attempt.submission_id = @submission.id
        @attempt.code = params[:code]
        @attempt.hint = nil
        @attempt.submitted_at = now
        @attempt.result_id = json.completed

        @attempt.save

        render json: http.response
      end
    end
  end


  def show
    @submission = Submission.find(params[:id])
  end

  # POST /submissions/init
  def init_server
    # Only allow submissions from users who are signed in
    if user_signed_in?
      # Super definitely make certain that the request is totally and completed un-escaped
      level = JSON.parse(params[:level])
      body = URI.unescape({
        levelID: params[:level_id],
        classID: params[:course_id],
        userID: current_user.id,
        level: level
      }.to_json.to_s)

      uri = ROUTING_SERVER + '/session/create'
      http = EM::HttpRequest.new(uri).post head: { user_token: current_user.id, "Content-Type" => 'application/json' }, body: body

      self.response_body = ''
      self.status = -1

      puts '\n\n#### Sent a request to Jason ####\n\n'

      http.callback do
        finish_request do
          puts '\n\n#### Session initialized, returning to client ####\n\n'
          render json: http.response
        end
      end

    else
      render status: 403 # Forbidden
    end
  end

  # POST /submissions/submit
  def submit_level
    # Only allow submissions from users who are signed in
    if user_signed_in?
      @info = submission_params
      @info[:language_id] = 1
      @info[:status_id] = 1

      # Explicitly set the user to avoid client side hijacking
      @info[:user_id] = current_user.id

      uri = ROUTING_SERVER + '/level/submit/' + params[:session_id]
      http = EM::HttpRequest.new(uri).post head: { user_token: current_user.id }, body: { codelines: params[:code] }

      self.response_body = ''
      self.status = -1

      puts '\n\n#### Sent a level grading request to Jason ####\n\n'

      finish_submission(http)
    else
      render status: 403 # Forbidden
    end

    render nothing: true
  end

  # POST /submissions/submit/challenge
  def submit_challenge
    if user_signed_in?
      @info = submission_params
      @info[:language_id] = 1
      @info[:status_id] = 1
      @info[:user_id] = current_user.id

      @challenge = Challenge.find(params[:challenge_id])

      uri = ROUTING_SERVER + '/challenge/submit/'
      http = EM::HttpRequest.new(uri).post head: { user_token: current_user.id }, body: {
        code: params[:code],
        validationCode: @challenge.validation_code,
        outname: @challenge.outname,
        objectiveid: @challenge.objective_id
      }

      self.reponse_body = ''
      self.status = -1

      puts '\n\n#### Sent an objective grading request to Jason ####\n\n'

      finish_submission(http)
    else
      render status: 403 # Forbidden
    end

    render nothing: true
  end



  # POST /submissions
  def create
    @submission = Submission.new(submission_params)

    if @submission.save
      redirect_to @submission, notice: 'Submission was successfully created.'
    else
      render :new
    end
  end

  # DELETE /submissions/1
  def destroy
    @submission.destroy
    redirect_to submissions_url, notice: 'Submission was successfully destroyed.'
  end

  def new
    render layout: 'containerless'
  end

  private
    # Only allow a trusted parameter "white list" through.
    def submission_params
      params.require(:submission).permit(:user_id, :course_id, :level_id, :language_id, :status_id, :code)
    end
end
