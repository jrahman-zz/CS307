class AddObjectiveIdToChallenges < ActiveRecord::Migration
  def change
    add_column :challenges, :objective_id, :integer
  end
end
