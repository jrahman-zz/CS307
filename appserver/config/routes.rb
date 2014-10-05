Rails.application.routes.draw do
  devise_for :users

  resources :levels, :submissions, :courses, :users

  root to: 'courses#index'
end
