from flask import Flask, jsonify, request, json
from CodeExecutor import execute

app = Flask(__name__)

appcontext = {} #Context for all code execution in this docker container

@app.route('/ping', methods=['GET'])
def get_health():
    print(request.data)
    return jsonify({'response':'PONG'})

@app.route('/level/<levelid>/submit', methods=['POST'])
def run_code(levelid):
    print('received request to run level: '+levelid)
    for item in request.form.items():
        print('form data item: '+str(item))
    try:
        loadedjson = json.loads(request.form['jsondata'])
        print("Codelines: " + '\n'.join(loadedjson['codelines']))
        #print("Context: " + loadedjson['context'])
    except Exception as e:
        print(e)

    code = '\n'.join(loadedjson['codelines'])
    if 'context' in loadedjson:
        print("Found a context")
        context = loadedjson['context']
    try:
        status = execute(code, context)
    except Exception as e:
        print(e)

    print('status:' + str(status))
    if len(status) == 0:
        return jsonify({'response':'Ran code'})
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
    return jsonify({'success': True, 'sessionID': ''})

# Run
if __name__ == '__main__':
    app.run(
        host = "0.0.0.0",
        port = 5000
    )
