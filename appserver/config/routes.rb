Rails.application.routes.draw do
  devise_for :users

  resources :levels, :submissions, :courses, :users

  get '/courses/:id/withdraw/:user_id' => 'courses#withdraw'

  root to: 'courses#index'
end
