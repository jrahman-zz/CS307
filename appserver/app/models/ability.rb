class Ability
  include CanCan::Ability

  def initialize(user)
    # Initialize guest user if not logged in
    user ||= User.new

    can :read, Level

    # Admins
    if user.has_role? :admin
      can :manage, :all

    # Instructors
    elsif user.has_role? :instructor
      Course.with_role(:instructor, user).each do |course|
        can :manage, course
      end


    # Students
    elsif user.has_role? :student
      Course.with_role(:student, user).each do |course|
        can [:read, :submit], course
      end
    else
      can :read, Course
      can :read, User
      can :manage, Course
    end
  end
end
