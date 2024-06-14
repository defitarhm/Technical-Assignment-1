from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api/data', methods=['POST'])
def receive_data():
    data = request.get_json()
    if 'mq_value' in data:
        mq_value = data['mq_value']
        print(f"Received MQ sensor value: {mq_value}")
        response = {
            'status': 'success',
            'mq_value': mq_value
        }
        return jsonify(response), 200
    else:
        return jsonify({'status': 'error', 'message': 'Invalid data'}), 400

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)  # Ganti dengan port server Anda
