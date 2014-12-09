class Attempt < ActiveRecord::Base
  belongs_to :submission
  has_one :attempt, as: :previous

  def completed
    result_id
  end
end
