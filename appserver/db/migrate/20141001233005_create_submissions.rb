class CreateSubmissions < ActiveRecord::Migration
  def change
    create_table :submissions do |t|
      t.references :user, index: true
      t.references :course, index: true
      t.text       :code
      t.boolean    :passed
      t.decimal    :score, precision: 6, scale: 2
      t.datetime   :submitted_at

      t.timestamps
    end
  end
end
