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
prefix = ''
suffix = ''

@app.route('/ping', methods=['GET'])
def get_health():
    print(request.data)
    return jsonify({'response':'PONG'})

@app.route('/objective/submit', methods=['POST'])
def submit_objective():
    global engine
    global appcontext
    loadedjson = request.get_json()

    try:
        code = loadedjson['codelines']
        validation = loadedjson['validationcode']
        outname = loadedjson['outname']
        objectiveid = loadedjson['objectiveid']
    except KeyError:
        return Response(status = 400)  #The json posted does not contain the keys we expected
    except Exception:
        return Response(status = 500)

    if not code or not validation or not outname or not objectiveid:
        return Response(status = 400)

    # TODO Probably should have some error checking for the various inputs
    
    code = code + "\n" + validation
    
    try:
        # Start objective
        engine.startObjective(objectiveid)
        print("started objective")
        ((success, message), status) = run_objective(code, outname)
        engine.endObjective(success)
    except Exception as e:
        print(str(e))
        engine.endObjective(False)
        return Response(status = 500)

    if len(status) == 0:
        if success:
	    return Response(response=engine.getResult(),
                  status=200,
                  mimetype="application/json")
	else:
            response=json.dumps({'response':'Incorrect answer',
                  'error_name':'IncorrectAnswer',
                  'error_obj':None,
                  'error_line_number':-1,
                  'error_line_text':'',
                  'error_message':message})

            return Response(response=response,    
		   status=200,
                   mimetype="application/json")
    else:
	response = json.dumps({'response':'Error running code',
                  'error_name':str(status['exc_type']),
                  'error_obj':str(status['exc_obj']),
                  'error_line_number':str(status['lineno']),
                  'error_line_text':str(status['line']),
                  'error_message':str(status['message'])})

	return Response(response=response,
		  status=200,
                  mimetype="application/json")

def run_objective(code, outname):
    global appcontext

    # Use empty dict for context since we don't want/need
    # context from the submission to carry over/carry in
    context = {}
    (context, status) = execute(code, appcontext)
    if len(status) != 0:
	return ((False, ""), status)
    if outname not in context:
        raise Exception("Result variable not found")
    return (context[outname], status)

@app.route('/level/submit', methods=['POST'])
def submit_level():
    global engine
    global appcontext
    loadedjson = request.get_json()
    code = loadedjson['codelines']
    try:
        engine.startSubmission()
        (appcontext, status) = execute(code, appcontext)
        engine.endSubmission()
    except Exception as e:
        print str(e)
        engine.endSubmission()
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
        print str(e)
        return Response(status=500)


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
