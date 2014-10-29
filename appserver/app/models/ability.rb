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
    end


    # Student Roles
    Course.with_role(:student, user).each do |course|
      can [:read, :submit, :withdraw], course
    end


    # Guest rolls
    can [:read, :approve_enrollment], Course

    # Users can manage themselves
    can :manage, user
  end
end
