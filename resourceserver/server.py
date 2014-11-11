#!/usr/bin/env python

from flask import Flask, abort, send_file
import logging
import yaml

# Local classes
from local_types import Resource, Database


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


logger = logging.getLogger(__name__)
level = logging.DEBUG if LOG_CONFIG['level'].lower() == 'debug' else logging.INFO
logging.basicConfig(filename=LOG_CONFIG['file'], level=level)
logging.info('Logging initialized')

app = Flask(__name__)
connection = Database(DB_CONFIG)



#######
### SERVER
#######

@app.route('/resource/<int:resource_id>', methods=['GET'])
def get_resource(resource_id):
  try:
    logging.debug('Fetching resource %d', resource_id)

    resource = connection.get(Resource, [resource_id])
  except Exception as e:
    logging.exception('Failed to get resource')
    abort(500)

  if resource == None:
    logging.info('Resource %d not found', resource_id)
    abort(404)

  logging.debug('Returning resource %d', resource_id)

  return send_file('resources/'+resource.file_name, mimetype=resource.mime_type)

@app.route('/ping', methods=['GET'])
def ping():
  try:
    logging.debug('Responding to ping')
    connection = get_connection(config)
  except:
    logging.exception('Failed to handle ping request')
    abort(500)

  return make_response(200, 'Pong')



#######
### MAIN
#######

if __name__ == "__main__":
  app.run(**SERVER_CONFIG)
