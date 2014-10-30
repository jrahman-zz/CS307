Rails.application.routes.draw do
  devise_for :users

  resources :levels, :submissions, :courses, :users

  # Courses
  post '/courses/:id/withdraw/:user_id' => 'courses#withdraw', as: :enrollment_withdraw
  post '/courses/:id/enroll/:user_id' => 'courses#enroll', as: :enrollment_create
  post '/courses/:id/approve_enrollment/:user_id' => 'courses#approve_enrollment', as: :enrollment_approve

  # Users
  get '/users/:id/admin_edit/:user_id' => 'users#admin_edit', as: :admin_edit

  # Submissions
  post '/submissions/submit/' => 'submissions#submit', as: :grade_submission

  # Static pages
  get '/pages/home' => 'pages#home'
  get '/pages/tutorial' => 'pages#tutorial'

  root to: 'pages#home'
end
