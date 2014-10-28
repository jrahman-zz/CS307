module ApplicationHelper
  def glyphicon icon
    "<span class=\"glyphicon glyphicon-#{icon}\"></span>".html_safe
  end
end
