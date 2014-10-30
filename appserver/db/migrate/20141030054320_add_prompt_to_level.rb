class AddPromptToLevel < ActiveRecord::Migration
  def change
    add_column :levels, :prompt, :text
  end
end
