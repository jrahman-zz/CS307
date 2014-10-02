class CreateLevels < ActiveRecord::Migration
  def change
    create_table :levels do |t|
      t.string     :name
      t.references :course, index: true
      t.text       :tilemap

      t.timestamps
    end
  end
end
