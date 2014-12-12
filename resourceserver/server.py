#!/usr/bin/env python

from flask import Flask, flash, abort, send_from_directory, render_template, redirect, url_for, request
from werkzeug import secure_filename
import logging
import os
import yaml

# Local classes
from local_types import Resource, ResourceType, Database


#######
### CONFIGURATION
#######

CONFIG_FILE = 'config.yaml'
# Allow for command line override
#   Ex: resource_server my_config.yaml
CONFIG_FILE = CONFIG_FILE or sys.argv[3]

USER_CONFIG   = yaml.load(open(CONFIG_FILE))
DB_CONFIG     = USER_CONFIG['db']
LOG_CONFIG    = USER_CONFIG['log']
SERVER_CONFIG = USER_CONFIG['server']

UPLOAD_FOLDER = 'resources'
ALLOWED_EXTENSIONS = frozenset(['txt', 'pdf', 'png', 'jpg', 'jpeg', 'gif'])


logger = logging.getLogger(__name__)
level = logging.DEBUG if LOG_CONFIG['level'].lower() == 'debug' else logging.INFO
logging.basicConfig(filename=LOG_CONFIG['file'], level=level)
logging.info('Logging initialized')

app = Flask(__name__)
app.secret_key = 'i_hate_making_secret_keys_:('
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
connection = Database(DB_CONFIG)



#######
### SERVER
#######

def allowed_file(filename):
  return '.' in filename and \
         filename.rsplit('.', 1)[1] in ALLOWED_EXTENSIONS


# Redirect the root URL
@app.route('/', methods=['GET'])
def root():
  return redirect(url_for('resources_index'))



### Resources ###

@app.route('/resources/', methods=['GET'])
def resources_index():
  resources = connection.all(Resource)
  types = { rt.id: rt for rt in connection.all(ResourceType) }

  return render_template('resources_index.html', resources=resources, resource_types=types)


@app.route('/resources/<int:resource_id>', methods=['GET'])
def resources_show(resource_id):
  try:
    logging.debug('Fetching resource %d', resource_id)

    resource = connection.get(Resource, [resource_id])[0]
  except Exception as e:
    logging.exception('Failed to get resource')
    abort(500)

  if not resource:
    logging.info('Resource %d not found', resource_id)
    abort(404)

  logging.debug('Returning resource %d', resource_id)

  return send_from_directory(app.config['UPLOAD_FOLDER'], resource.file_name)


@app.route('/resources/new', methods=['GET'])
def resources_new():
  return render_template('resources_new.html', resource_types=connection.all(ResourceType))


@app.route('/resources/create', methods=['POST'])
def resources_create():
  file = request.files['file']
  if file and allowed_file(file.filename):
    file_name = secure_filename(file.filename)
    resource_type = request.form['type']
    file.save(os.path.join(app.config['UPLOAD_FOLDER'], file_name))

    connection.create(Resource, file_name=file_name, resource_type=resource_type)

    flash('Resource "%s" successfully created' % file_name, 'success')
    return redirect(url_for('resources_index'))

  # If no file was provided, or if the file was invalid
  else:
    return redirect(url_for('resources_new', message='Invalid file', message_type='warning'))

@app.route('/resources/<int:resource_id>/destroy', methods=['DELETE', 'GET'])
def resources_destroy(resource_id):
  r = connection.get(Resource, [resource_id])[0]
  connection.destroy(Resource, [resource_id])

  # Delete the resoource file
  os.remove(os.path.join(app.config['UPLOAD_FOLDER'], r.file_name))

  flash('Resource "%s" successfully removed (id: %d)' % (r.file_name, r.id), 'success')
  return redirect(url_for('resources_index'))



### Resource Types ###

@app.route('/resource_types/new', methods=['GET'])
def resource_types_new():
  return render_template('resource_types_new.html')


@app.route('/resource_types/create', methods=['POST'])
def resource_types_create():
  name = request.form['name']
  connection.create(ResourceType, name=name)

  flash('ResourceType "%s" successfully created' % name, 'success')
  return redirect(url_for('resources_index'))

@app.route('/resource_types/<int:resource_type_id>/destroy', methods=['DELETE', 'GET'])
def resource_types_destroy(resource_type_id):
  rt = connection.get(ResourceType, [resource_type_id])[0]
  connection.destroy(ResourceType, [resource_type_id])

  flash('ResourceType "%s" successfully removed (id: %d)' % (rt.name, rt.id), 'success')
  return redirect(url_for('resources_index'))



### Utility ###

@app.route('/ping', methods=['GET'])
def ping():
  try:
    logging.debug('Responding to ping')
    return make_response(200, 'Pong')
  except:
    logging.exception('Failed to handle ping request')
    abort(500)


# Ensure a fresh page load every time
@app.after_request
def add_header(response):
    """
    Add headers to both force latest IE rendering engine or Chrome Frame,
    and also to cache the rendered page for 10 minutes.
    """
    response.headers['X-UA-Compatible'] = 'IE=Edge,chrome=1'
    response.headers['Cache-Control'] = 'public, max-age=0'
    return response


#######
### MAIN
#######

if __name__ == "__main__":
  app.run(**SERVER_CONFIG)
