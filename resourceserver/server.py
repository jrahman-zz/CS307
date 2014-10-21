#!/usr/bin/env python

from flask import Flask, abort
import mysql.connector
import logging
import yaml

logger = logging.getLogger(__name__)
app = Flask(__name__)

def get_config():
	with open('config.yaml') as f:
		res = yaml.load(f)
	return res

config = get_config()

# Init logger
def config_logging(config):
	if config['log']['level'].lower() == 'debug':
		level = logging.DEBUG
	else:
		level = logging.INFO
	logging.basicConfig(filename=config['log']['file'], level=level)
	logging.info('Logging initialized')

class Resource:
	def __init__(self, data, mime_type, resource_type):
		self.data = data
		self.mime_type = mime_type
		self.resource_type = resource_type

def get_connection(config):
	username 	= config['db']['username']
	password 	= config['db']['password']
	hostname 	= config['db']['hostname']
	port 		= config['db']['port']
	database 	= config['db']['name']	

	connection = mysql.connector.connect(user=username,\
					password=password,\
					host=hostname,\
					port=port,\
					database=database)
	return connection


def get_resource(connection, resource_id):
	result = None	
	with connection.cursor() as cursor:
		query = """
			SELECT
				data,
				mimetype,
				type
			FROM resources
			WHERE id = %d""" % resource_id
		cursor.execute(query)
		result = cursor.fetchone()
	
	if result == None:
		return None
	(data, mime_type, resource_type) = result
	return Resource(data, mime_type, resource_type)
	

@app.route('/resource/<int:resource_id>', methods=['GET'])
def handle_request(resource_id):
	try:	
		logging.debug('Fetching resource %d', resource_id)
		connection = get_connection(config)
		resource = get_resource(connection, resouce_id)
	except Exception as e:
		logging.exception('Failed to get resource')
		abort(500)
	if resource == None:
		logging.info('Resource %d not found', resource_id)
		abort(404)

	logging.debug('Returning resource %d', resource_id)
	return make_response(resource.data, 200, mimetype=resource.mime_type)

@app.route('/ping', methods=['GET'])
def ping():
	try:
		logging.debug('Responding to ping')
		connection = get_connection(config)
	except:
		logging.exception('Failed to handle ping request')
		abort(500)
	
	return make_response(200, "Pong")

if __name__ == "__main__":
	config_logging(config)
	app.run(host=config['server']['hostname'],\
		port=config['server']['port'],\
		debug=True)
