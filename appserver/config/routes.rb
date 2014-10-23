Rails.application.routes.draw do
  devise_for :users

  resources :levels, :submissions, :courses, :users

  # Courses
  get '/courses/:id/withdraw/:user_id' => 'courses#withdraw', as: :courses_withdraw
  get '/courses/:id/approve_enrollment/:user_id' => 'courses#approve_enrollment', as: :courses_approve_enrollment #change to post later

  # Users
  get '/users/:id/admin_edit/:user_id' => 'users#admin_edit', as: :admin_edit

  # Submissions
  post '/submissions/submit/' => 'submissions#submit', as: :grade_submission

  # Static pages
  get '/pages/home' => 'pages#home'

  root to: 'pages#home'
end
