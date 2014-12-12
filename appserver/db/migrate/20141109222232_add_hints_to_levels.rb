class AddHintsToLevels < ActiveRecord::Migration
  def change
  	add_column :levels, :hint, :text
  end
end
