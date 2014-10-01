#!/bin/env python

from flask import Flask
app = Flask(__name__)

@app.route("/")
def hello():
	return "Welcome to the grading server!", 200

@app.route('/session', methods=['POST'])
def create_session():
	pass

@app.route('/session', methods=['GET'])
def get_session():
	pass

@app.route('/session/<id>', methods=['DELETE'])
def delete_session():
	pass

@app.route('/submit', methods=['POST'])
def submit():
	pass

@app.route('/submit/<int:subid>', methods=['GET'])
def get_submission():
	pass

@app.route('/docs', methods=['GET'])
def get_documentation():
	pass

@app.route('/ping', methods=['GET'])
def ping():
	pass

if __name__ == "__main__":
	app.run()
