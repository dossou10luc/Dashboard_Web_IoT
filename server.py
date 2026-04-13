from flask import Flask, request, jsonify, render_template
from flask_socketio import SocketIO

app = Flask(__name__)
socketio = SocketIO(app, cors_allowed_origins="*")

data_store = {
    "temperature": 0,
    "humidity": 0
}

@app.route('/')
def index():
    return render_template("index.html")

@app.route('/upload', methods=['POST'])
def upload():
    data = request.json
    temperature = data.get("temperature")
    humidity = data.get("humidity")

    data_store["temperature"] = temperature
    data_store["humidity"] = humidity

    # 🔥 envoi temps réel
    socketio.emit('sensor_data', data_store)

    print(f"Température: {temperature} °C | Humidité: {humidity} %")

    return jsonify({"status": "ok"}), 200

if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5000)