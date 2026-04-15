#include <WiFi.h>   // Bibliothèque pour la connexion WiFi de l'ESP32
#include <HTTPClient.h>   // Bibliothèque pour envoyer des requêtes HTTP
#include "DHT.h"   // Bibliothèque pour le capteur DHT (température + humidité)

// Définition du pin où est connecté le capteur DHT22
#define DHTPIN 15
// Type de capteur utilisé (DHT22)
#define DHTTYPE DHT22

// Paramètres de connexion WiFi (réseau Wokwi)
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// URL du serveur (via ngrok) pour envoyer les données
const char* serverName = "http://grumpily-accent-waviness.ngrok-free.dev/upload";
// Initialisation du capteur DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialisation de la communication série (pour affichage dans le moniteur)
  Serial.begin(115200);
  // Connexion au réseau WiFi
  WiFi.begin(ssid, password);

  // Boucle jusqu'à ce que la connexion soit établie
  Serial.print("Connexion WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);  // attendre 1 seconde
    Serial.print(".");  // afficher progression
  }
  // Confirmation de connexion
  Serial.println("Connecté !");
  // Initialisation du capteur DHT
  dht.begin();
}

void loop() {
  // Vérifie si l'ESP32 est toujours connecté au WiFi
  if (WiFi.status() == WL_CONNECTED) {
    // Lecture de la température (en °C)
    float temperature = dht.readTemperature();
    // Lecture de l'humidité (en %)
    float humidity = dht.readHumidity();

    // Vérifie que les valeurs ne sont pas invalides (NaN)
    if (!isnan(temperature) && !isnan(humidity)) {
      // Création d'un objet HTTP pour envoyer les données
      HTTPClient http;
      // Initialisation de la requête vers le serveur
      http.begin(serverName);
      // Définition du type de contenu (JSON)
      http.addHeader("Content-Type", "application/json");
      // Création des données JSON à envoyer
      String jsonData = "{\"temperature\":" + String(temperature) +
                        ",\"humidity\":" + String(humidity) + "}";
      // Affichage des données envoyées dans le moniteur série
      Serial.println("Envoi données...");
      Serial.println(jsonData);
      // Envoi de la requête POST avec les données
      int httpResponseCode = http.POST(jsonData);
      // Affichage du code de réponse du serveur (200 = OK)
      Serial.print("Code réponse: ");
      Serial.println(httpResponseCode);

      // Fermeture de la connexion HTTP
      http.end();
    }
  }
  // Attente de 10 secondes avant la prochaine mesure
  delay(10000);
}