module ApplicationHelper
  def glyphicon icon
    "<span class=\"glyphicon glyphicon-#{icon}\"></span>".html_safe
  end

  def checkmark bool, color
    mark = glyphicon (bool ? 'ok' : 'remove')
    if color
      mark = '<span class="text-'+(bool ? 'success' : 'danger')+'">'+mark+'</span>'
    end

    mark.html_safe
  end
end
