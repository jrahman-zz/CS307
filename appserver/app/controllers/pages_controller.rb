class PagesController < ApplicationController
  layout 'static'

  def home
    @user = User.new
  end
end
