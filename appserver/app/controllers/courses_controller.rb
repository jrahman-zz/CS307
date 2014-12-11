class CoursesController < ApplicationController
  before_action :set_course, only: [:show, :edit, :update, :destroy, :enroll, :withdraw, :approve_enrollment]

  authorize_resource

  # GET /courses
  def index
    @q = Course.search(params[:q])
    @courses = @q.result(distinct: true)
  end

  # GET /courses/1
  def show
  end

  # GET /courses/new
  def new
    @course = Course.new
  end

  # GET /courses/1/edit
  def edit
  end

  # POST /courses
  def create
    @course = Course.new(course_params)

    if @course.save
      redirect_to @course, notice: 'Course was successfully created.'
    else
      render :new
    end
  end

  # PATCH/PUT /courses/1
  def update
    if @course.update(course_params)
      redirect_to @course, notice: 'Course was successfully updated.'
    else
      render :edit
    end
  end

  # DELETE /courses/1
  def destroy
    @course.destroy
    redirect_to courses_url, notice: 'Course was successfully destroyed.'
  end

  def withdraw
    @user = User.find(params[:user_id])

    @user.revoke :student, @course
    @user.revoke :pending_student, @course

    redirect_to @course, notice: 'You have successfully withdrawn!'
  end

  def enroll
    @user = User.find(params[:user_id])

    if @course.open
      @user.grant :student, @course
      flash[:notice] = 'Successfully enrolled in ' + @course.name
    else
      @user.grant :pending_student, @course
      flash[:notice] = 'Pending enrollment approval for ' + @course.name
    end

    redirect_to @course
  end

  def approve_enrollment
  	@user = User.find(params[:user_id])

    @user.revoke :pending_student, @course
 	  @user.grant :student, @course

    redirect_to @course
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_course
      @course = Course.find(params[:id])
    end

    # Only allow a trusted parameter "white list" through.
    def course_params
      params.require(:course).permit(:name, :start_date, :description, :open)
    end
end
