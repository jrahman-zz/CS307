from flask import Flask, jsonify

app = Flask(__name__)


@app.route('/health', methods=['GET'])
def get_health():
    return jsonify({'response':'PONG'})



if __name__ == '__main__':
    app.run(debug=True)
