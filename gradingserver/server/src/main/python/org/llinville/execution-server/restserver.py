from flask import Flask, jsonify
55
app = Flask(__name__)


@app.route('/health', methods=['GET'])
def get_health():
    return jsonify({'response':'PONG'})

@app.route('level/<id>/submit', methods=['POST'])
def submit_code():
    if
    return json

# Run
if __name__ == '__main__':
    app.run(
        host = "0.0.0.0",
        port = 5000
    )
