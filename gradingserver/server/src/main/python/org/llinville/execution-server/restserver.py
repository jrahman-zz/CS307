from flask import Flask, jsonify, request
from codeexecutor import execute

app = Flask(__name__)


@app.route('/health', methods=['GET'])
def get_health():
    print(request.data)
    return jsonify({'response':'PONG'})

@app.route('/level/<levelid>/submit', methods=['POST'])
def run_code(levelid):
    print('received request to run level: '+levelid)
    print('code: ' + request.form['code'])
    status = execute(request.form['code'])
    if status:
        return jsonify({'response':'Ran code'})
    else:
        return jsonify({'response':'Error running code'})


# Run
if __name__ == '__main__':
    app.run(
        host = "0.0.0.0",
        port = 5000
    )
