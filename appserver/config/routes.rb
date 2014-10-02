Rails.application.routes.draw do
  resources :levels, :submissions, :courses, :users
end
