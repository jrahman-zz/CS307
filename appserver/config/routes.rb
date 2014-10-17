Rails.application.routes.draw do
  devise_for :users

  resources :levels, :submissions, :courses, :users

  get '/courses/:id/withdraw/:user_id' => 'courses#withdraw', as: :courses_withdraw
  
  get '/courses/:id/approve_enrollment/:user_id' => 'courses#approve_enrollment', as: :courses_approve_enrollment #change to post later

  get '/users/:id/admin_edit/:user_id' => 'users#admin_edit', as: :admin_edit

  root to: 'courses#index'
end
