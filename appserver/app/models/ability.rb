class Ability
  include CanCan::Ability

  def initialize(user)
    # Initialize guest user if not logged in
    user ||= User.new(id: 0)

    # Admin role?
    if user.has_role? :admin
      can :manage, :all
    end

    # Instructor roles
    Course.with_role(:instructor, user).each do |course|
      can :manage, course
      can :manage, course.levels
      can :manage, Role, resource_id: course.id, resource_type: "Course"
    end


    # Student roles
    Course.with_role(:student, user).each do |course|
      can [:read, :submit, :withdraw], course
      can [:read, :play], course.levels
    end


    # Guest roles
    can [:read, :enroll], Course


    # Users can manage themselves
    can :manage, user
  end
end
