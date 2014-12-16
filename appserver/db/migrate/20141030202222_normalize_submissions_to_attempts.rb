class NormalizeSubmissionsToAttempts < ActiveRecord::Migration
  def change
    create_table :attempts do |t|
      t.text :code

      t.text :hint
      t.datetime :submitted_at

      t.references :submission, index: true
      t.references :previous, index: true
      t.references :result, index: true
    end

    change_table :submissions do |t|
      t.remove :code
      t.remove :score
      t.remove :passed
      t.remove :submitted_at

      t.datetime :started_at
      t.datetime :completed_at

      t.references :status, index: true
      t.references :language, index: true
    end

    create_table :statuses do |t|
      t.string :name
      t.text :description
    end
  end
end
