Rails.application.routes.draw do
  devise_for :users

  # Levels
  get  '/levels/:id/play' => 'levels#play', as: :play_level
  get  '/levels/:id/submissions' => 'levels#submissions', as: :level_submissions

  # Courses
  post '/courses/:id/withdraw/:user_id' => 'courses#withdraw', as: :enrollment_withdraw
  post '/courses/:id/enroll/:user_id' => 'courses#enroll', as: :enrollment_create
  post '/courses/:id/approve_enrollment/:user_id' => 'courses#approve_enrollment', as: :enrollment_approve

  # Users
  get  '/users/:id/admin_edit/:user_id' => 'users#admin_edit', as: :admin_edit

  # Submissions
  post '/submissions/submit/' => 'submissions#submit', as: :grade_submission

  # Attempts
  get '/attempts/compare' => 'attempts#compare', as: :attempt_comparison

  # Static pages
  get  '/pages/home' => 'pages#home'
  get  '/pages/tutorial' => 'pages#tutorial'


  resources :levels, :submissions, :courses, :users, :attempts

  root to: 'pages#home'
end
