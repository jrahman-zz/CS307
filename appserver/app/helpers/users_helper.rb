module UsersHelper
	def course_progress course, user
		course.levels.count / Submission.where.not(completed_at: nil).where(user: user,course: course).count rescue 0
	end
end
