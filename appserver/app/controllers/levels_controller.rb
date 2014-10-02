class LevelsController < ApplicationController
  before_action :set_level, only: [:show, :edit, :update, :destroy]

  # GET /levels
  def index
    @levels = Level.all
  end

  # GET /levels/1
  def show
  end

  # GET /levels/new
  def new
    @level = Level.new
  end

  # GET /levels/1/edit
  def edit
  end

  # POST /levels
  def create
    @level = Level.new(level_params)

    if @level.save
      redirect_to @level, notice: 'Level was successfully created.'
    else
      render :new
    end
  end

  # PATCH/PUT /levels/1
  def update
    if @level.update(level_params)
      redirect_to @level, notice: 'Level was successfully updated.'
    else
      render :edit
    end
  end

  # DELETE /levels/1
  def destroy
    @level.destroy
    redirect_to levels_url, notice: 'Level was successfully destroyed.'
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_level
      @level = Level.find(params[:id])
    end

    # Only allow a trusted parameter "white list" through.
    def level_params
      params.require(:level).permit(:name, :course_id_id, :tilemap)
    end
end
