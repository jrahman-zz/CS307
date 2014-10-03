class CreateCourses < ActiveRecord::Migration
  def change
    create_table :courses do |t|
      t.string   :name
      t.datetime :start_date

      t.timestamps
    end
  end
end
