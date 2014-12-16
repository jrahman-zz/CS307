class AddLevelIdToSubmission < ActiveRecord::Migration
  def change
    add_reference :submissions, :level, index: true
  end
end
