#!/usr/bin/env

from time import sleep
from flask import Flask, jsonify, request, json, Response
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
    global engine
    global appcontext
    loadedjson = request.get_json()
    code = loadedjson['codelines']
    try:
        (appcontext, status) = execute(code, appcontext, engine)
    except Exception as e:
        print str(e)
        return Response(status = 500)

    print('status:' + str(status))
    if len(status) == 0:
        return Response(response=engine.getResult(),
                    status=200,
                    mimetype="application/json")
    else:
        response = json.dumps({'response':'Error running code',
                        'error_name':str(status['exc_type']),
                        'error_obj':str(status['exc_obj']),
                        'error_line_number':str(status['lineno']),
                        'error_line_text':str(status['line']),
                        'error_message':str(status['message'])})
        print response
        return Response(
                response = response,
                status = 200,
                mimetype = "application/json"
            )

@app.route('/initialize', methods=['POST'])
def init_engine():
    # Create game engine instance from the game library
    # And create initial context only containing a copy
    # Of the world and hero fascade objects
<<<<<<< HEAD
    global engine
    global appcontext
    try:
        appcontext = {}
        engine = gamelib.Engine(request.data)
        appcontext['hero'] = engine.getHero()
        return Response(
                response = """{ "success": true, "sessionID": "" }""",
                status = 200,
                mimetype = "application/json"
            )
    except Exception as e:
        return Response(status=500)
=======
    # TODO
    appcontext = {}
    engine = gamelib.Engine(request.data)
    appcontext['hero'] = gamelib.getHero()
    return jsonify({'success': True, 'sessionID': ''})
>>>>>>> parent of 2b3a9e1... gamelib.Engine changed to engine

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
