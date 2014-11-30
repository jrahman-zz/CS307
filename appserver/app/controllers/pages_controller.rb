class PagesController < ApplicationController
  layout 'static'

  def home
    @user = User.new
  end

  def tutorial
  end

  def credit
  end

end
