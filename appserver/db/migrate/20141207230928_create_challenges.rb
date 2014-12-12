class CreateChallenges < ActiveRecord::Migration
  def change
    create_table :challenges do |t|
      t.belongs_to :level
      t.text :validation_code
      t.string :outname

      t.timestamps
    end
  end
end
