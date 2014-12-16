class Submission < ActiveRecord::Base
  belongs_to :user
  belongs_to :course
  belongs_to :level

  has_one :status
  has_one :language

  has_many :attempts
end
