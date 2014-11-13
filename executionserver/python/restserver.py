#!/usr/bin/env

from time import sleep
from flask import Flask, jsonify, request, json
from codeexecutor import execute
import sys
import os
import argparse

sys.path.append('.')
import gamelib

app = Flask(__name__)

engine = None
appcontext = {} #Context for all code execution in this docker container

@app.route('/ping', methods=['GET'])
def get_health():
    print(request.data)
    return jsonify({'response':'PONG'})

@app.route('/level/submit', methods=['POST'])
def run_code():
    # for item in request.form.items():
    #     print('form data item: '+str(item))
    # try:
    #     loadedjson = json.loads(request.form['jsondata'])
    #     print("Codelines: " + '\n'.join(loadedjson['codelines']))
    #     #print("Context: " + loadedjson['context'])
    # except Exception as e:
    #     print(e)
    #
    # code = '\n'.join(loadedjson['codelines'])
    # if 'context' in loadedjson:
    #     print("Found a context")
    #     context = loadedjson['context']
    #
    loadedjson = request.get_json()
    code = loadedjson['codelines']
    try:
        status = execute(code, appcontext, engine)
    except Exception as e:
        print(e)

    print('status:' + str(status))
    if len(status) == 0:
        nullline=None #so I can comment out the next line
        return engine.getResult()
    else:
        return jsonify({'response':'Error running code',
                        'error_name':str(status['exc_type']),
                        'error_obj':str(status['exc_obj']),
                        'error_line_number':str(status['lineno']),
                        'error_line_text':str(status['line']),
                        'error_message':str(status['message'])})

@app.route('/initialize', methods=['POST'])
def init_engine():
    # Create game engine instance from the game library
    # And create initial context only containing a copy
    # Of the world and hero fascade objects
    # TODO
    appcontext = {}
    engine = gamelib.Engine(request.data)
    appcontext['hero'] = gamelib.getHero()
    return jsonify({'success': True, 'sessionID': ''})

#retrieve a value from the context of this execution server
#for unit testing purposes
@app.route('/retrieve/<key>', methods=['GET'])
def get_variable(key):
    value = ''
    try:
        value = appcontext[key]
    except KeyError:
        return jsonify({'error':'KeyError'})
    return jsonify({'value':value})

@app.route('/shutdown/<timems>', methods=['POST'])
def shutdown(timems):
    sleep(0.001 * timems)
    sys.exit(0)

# Run
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Start the REST interface for Execution Server')
    parser.add_argument('-p','--port', type=int, default = 5000,
                        help='The PORT on which to run the Execution Server listener (default = %(default)s)')
    parser.add_argument('-H','--host', type=str, default = '0.0.0.0',
                        help='The HOST on which to run the Execution Server listener (default = %(default)s)')

    args = parser.parse_args()
    print('starting rest server on '+args.host+':'+str(args.port))
    app.run(
        host = args.host,
        port = args.port
    )
