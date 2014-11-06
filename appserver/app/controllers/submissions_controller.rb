class SubmissionsController < ApplicationController
  # Allow submissions to be handled asynchronously
  include AsyncController

  def show
    @submission = Submission.find(params[:id])
  end

  def init_server
    # Only allow submissions from users who are signed in
    if user_signed_in?
      uri = 'http://klamath.dnsdynamic.com:8088/session/create'
      http = EM::HttpRequest.new(uri).post head: { user_token: current_user.id }, body: params[:level]

      http.callback do
        finish_request do
          render json: http.response
        end
      end

    else
      render status: 403 # Forbidden
    end
  end

  def submit
    # Only allow submissions from users who are signed in
    if user_signed_in?

      @info = submission_params
      @info[:language_id] = 1
      @info[:status_id] = 1

      # Explicitly set the user to avoid client side hijacking
      @info[:user_id] = current_user.id

      uri = 'http://klamath.dnsdynamic.com:8088/level/submit/'
      http = EM::HttpRequest.new(uri).post head: { user_token: current_user.id }, body: params[:code]

      http.callback do
        finish_request do
          render json: http.response
        end
      end

      @submission = Submission.find_or_create_by(@info)
      @submission.save


      @attempt = Attempt.new
      @attempt.submission_id = @submission.id
      @attempt.code = params[:code]
      @attempt.hint = nil
      @attempt.submitted_at = Time.now

      @attempt.save
    else
      render status: 403 # Forbidden
    end

    render json: @attempt
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
