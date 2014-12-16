class AttemptsController < ApplicationController
  def show
    @attempt = Attempt.find(params[:id])
  end

  def compare
    @from = Attempt.find(params[:attempts][:from])
    @to = Attempt.find(params[:attempts][:to])
  end
end
