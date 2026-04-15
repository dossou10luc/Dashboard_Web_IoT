from flask import Flask, request, jsonify, render_template  # Import des modules Flask
from flask_socketio import SocketIO   # Import de Socket.IO pour le temps réel

# Initialisation de l'application Flask
app = Flask(__name__)
# Initialisation de Socket.IO (permet communication temps réel avec le frontend)
socketio = SocketIO(app, cors_allowed_origins="*")

# Dictionnaire pour stocker les données capteur
data_store = {
    "temperature": 0,
    "humidity": 0
}

# Route principale → affiche le dashboard
@app.route('/')
def index():
    return render_template("index.html")

# Route API pour recevoir les données de l’ESP32
@app.route('/upload', methods=['POST'])
def upload():
    # Récupération des données JSON envoyées par ESP32
    data = request.json
    # Extraction des valeurs
    temperature = data.get("temperature")
    humidity = data.get("humidity")

    # Mise à jour des données stockées
    data_store["temperature"] = temperature
    data_store["humidity"] = humidity

    # Envoi des données au dashboard en temps réel via Socket.IO
    socketio.emit('sensor_data', data_store)

    # Affichage dans le terminal (debug)
    print(f"Température: {temperature} °C | Humidité: {humidity} %")

    # Réponse envoyée à l’ESP32
    return jsonify({"status": "ok"}), 200

# Lancement du serveur Flask avec Socket.IO
if __name__ == '__main__':
    socketio.run(app, host='0.0.0.0', port=5000)