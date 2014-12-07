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
  # This will become:
  # post '/submissions/submit/level' => 'submissions#submit_level', as: :grade_submission
  post '/submissions/submit/' => 'submissions#submit', as: :grade_submission
  # post '/submissions/submit/challenge' => 'submissions#submit_challenge', as: :grade_challenge
  post '/submissions/init' => 'submissions#init_server', as: :init_grading_session

  # Attempts
  get '/attempts/compare' => 'attempts#compare', as: :attempt_comparison

  # Static pages
  get  '/pages/home' => 'pages#home'
  get  '/pages/tutorial' => 'pages#tutorial'
  get  '/pages/credit' => 'pages#credit'


  resources :levels, :submissions, :courses, :users, :attempts

  root to: 'pages#home'
end
