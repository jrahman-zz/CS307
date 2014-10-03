# encoding: UTF-8
# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# Note that this schema.rb definition is the authoritative source for your
# database schema. If you need to create the application database on another
# system, you should be using db:schema:load, not running all the migrations
# from scratch. The latter is a flawed and unsustainable approach (the more migrations
# you'll amass, the slower it'll run and the greater likelihood for issues).
#
# It's strongly recommended that you check this file into your version control system.

ActiveRecord::Schema.define(version: 20141001233458) do

  create_table "courses", force: true do |t|
    t.string   "name"
    t.datetime "start_date"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "levels", force: true do |t|
    t.string   "name"
    t.integer  "course_id"
    t.text     "tilemap"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  add_index "levels", ["course_id"], name: "index_levels_on_course_id", using: :btree

  create_table "submissions", force: true do |t|
    t.integer  "user_id"
    t.integer  "course_id"
    t.text     "code"
    t.boolean  "passed"
    t.decimal  "score",        precision: 6, scale: 2
    t.datetime "submitted_at"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  add_index "submissions", ["course_id"], name: "index_submissions_on_course_id", using: :btree
  add_index "submissions", ["user_id"], name: "index_submissions_on_user_id", using: :btree

  create_table "users", force: true do |t|
    t.string   "name"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

end
