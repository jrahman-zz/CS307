class Course < ActiveRecord::Base
  has_many :levels

  resourcify
end
