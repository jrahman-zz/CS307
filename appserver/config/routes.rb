Rails.application.routes.draw do
  devise_for :users

  resources :levels, :submissions, :courses, :users

  get '/courses/:id/withdraw/:user_id' => 'courses#withdraw', as: :courses_withdraw
<<<<<<< HEAD
  
  get '/courses/:id/approve_enrollment/:user_id' => 'courses#approve_enrollment', as: :courses_approve_enrollment #change to post later

  get '/users/:id/admin_edit/:user_id' => 'users#admin_edit', as: :admin_edit

  root to: 'courses#index'
=======

  get '/courses/:id/approve_enrollment/:user_id' => 'courses#approve_enrollment', as: :courses_approve_enrollment #change to post later

  get '/pages/home' => 'pages#home'
  root to: 'pages#home'
>>>>>>> 8be1e35c984ed237cdff9f878f72f47ebb69f434
end
