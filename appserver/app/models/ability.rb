class Ability
  include CanCan::Ability

  def initialize(user)
    # Guest roles
    can [:read], Course

    if user
      # Admin role
      if user.has_role? :admin
        can :manage, :all
      end

      # Instructor roles
      if Role.find_by(name: 'instructor')
        Course.with_role(:instructor, user).each do |course|
          can :manage, course
          can :manage, course.levels
          can :manage, Role, resource_id: course.id, resource_type: "Course"
        end
      end


      # Student roles
      if Role.find_by(name: 'student')
        Course.with_role(:student, user).each do |course|
          can [:read, :submit, :withdraw], course
          can [:read, :play], course.levels
        end
      end

      # Users can manage themselves
      can :manage, user

      # Users can enroll and withdraw from courses
      can [:enroll, :withdraw], Course
    end
  end
end
