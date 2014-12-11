module TutorialsHelper
  TUTORIAL_SECTIONS = {
    'User Management' => [
      'Creating a New User',
      'Accessing Account Details',
      'Editing or Deleting Your Account'
    ],
    'Course Management' => [
      'Creating a New Course',
      'Viewing a Course\'s Page',
      'Enrolling In or Withdrawing From a Course',
      'Managing Users Withing a Course'
    ],
    'Gameplay' => [
      'Playing a Level',
      'Testing Out Your Code'
    ]
  }

  def sidebar_nav
    capture_haml do
      haml_tag 'ul.sidebar_nav' do
        TUTORIAL_SECTIONS.each do |sec, sub_sections|
          haml_tag 'li.sidebar_section' do
            haml_tag 'a.sidebar_nav_link', sec, href: '#' + sec.parameterize('_')

            haml_tag 'ul.sidebar_section_nav' do
              sub_sections.each do |sub_sec|
                haml_tag 'li.sidebar_subsection' do
                  haml_tag 'a.sidebar_nav_link', sub_sec, href: '#' + sub_sec.parameterize('_')
                end
              end
            end
          end
        end
      end
    end
  end
end
