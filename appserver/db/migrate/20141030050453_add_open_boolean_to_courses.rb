class AddOpenBooleanToCourses < ActiveRecord::Migration
  def change
    add_column :courses, :open, :boolean
  end
end
