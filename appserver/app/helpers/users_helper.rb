module UsersHelper
	def course_progress course, user
		progress = course.levels.count / Submission.where.not(completed_at: nil).where(user: user,course: course).count rescue 0

    case progress
      when 0..19
        bar_type = 'danger'
      when 20..60
        bar_type = 'warning'
      when 60..99
        bar_type = 'info'
      when 100
        bar_type = 'success'
    end

    attrs = {
      'aria-valuemax' => 100,
      'aria-valuemin' => 0,
      'aria-valuenow' => progress,
      role: 'progressbar',
      style: "width: #{progress}%;",
      class: 'progress-bar progress-bar-striped progress-bar-' + bar_type
    }

    haml_tag :div, class: 'progress' do
      haml_tag :div, attrs do
        haml_tag :span, progress.to_s + '%'
      end
    end
	end
end
