Rails.application.routes.draw do
  devise_for :users

  resources :levels, :submissions, :courses, :users

  get '/courses/:id/withdraw/:user_id' => 'courses#withdraw'
	
  get '/courses/:id/approve_enrollment/:user_id' => 'courses#approve_enrollment' #change to post later

  root to: 'courses#index'
end
