class SubmissionsController < ApplicationController
  # Allow submissions to be handled asynchronously
  include AsyncController

  def submit
    # Only allow submissions from users who are signed in
    if user_signed_in?
      code = submission_params[:code]
      level_id = params[:level_id]
      course_id = params[:course_id]
      user_id = current_user.id

      @info = { code: code, level_id: level_id, course_id: course_id, user_id: user_id }
      render json: @info


    #   uri = 'http://klamath.dnsdynamic.com' #TODO replace with grading server location
    #   http = EM::HttpRequest.new(uri).post body: @info

    #   http.callback do
    #     finish_request do
    #       render json: http.response
    #     end
    #   end

    #   self.response_body = ''
    #   self.status = -1
    # else
      # render status: 403 # Forbidden
    end
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
      params.require(:submission).permit(:user_id, :course_id, :code, :passed, :score, :score, :submitted_at)
    end
end
