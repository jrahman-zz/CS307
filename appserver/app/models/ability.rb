class Ability
  include CanCan::Ability

  def initialize(user)
    # Initialize guest user if not logged in
    user ||= User.new

    # Admin role?
    if user.has_role? :admin
      can :manage, :all
    end

    # Instructor roles
    Course.with_role(:instructor, user).each do |course|
      can :manage, course
      can :manage, Level, course_id: course.id
    end


    # Student Roles
    Course.with_role(:student, user).each do |course|
      can [:read, :submit, :withdraw], course
    end


    # Guest roles
    can [:read, :approve_enrollment], Course

    # Users can manage themselves
    can :manage, user

    # TODO: TEMP FIX
    can :manage, Level
  end
end
