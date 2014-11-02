class Attempt < ActiveRecord::Base
  belongs_to :submission
  has_one :status, as: :result
  has_one :attempt, as: :previous
end
