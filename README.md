#  Projet IoT : Création d’un Dashboard Web de Visualisation de Donné IoT

## Étudiant

**DOSSOU KOKO Mahugnon Dieu-Donné Luc**

---

## Objectif du projet

Ce projet a pour objectif de concevoir un système IoT complet permettant :

* La collecte de données environnementales (température et humidité)
* La transmission de ces données vers un serveur web
* La visualisation en temps réel sur un dashboard interactif

---

## Architecture du système

```text
Capteur DHT22 → ESP32 (Wokwi) → HTTP (ngrok) → Flask → Socket.IO → Dashboard Web
```

---

## ⚙️ Technologies utilisées

| Technologie | Rôle                           |
| ----------- | ------------------------------ |
| ESP32       | Microcontrôleur IoT            |
| DHT22       | Capteur température & humidité |
| Flask       | Backend (API REST)             |
| Socket.IO   | Communication temps réel       |
| Chart.js    | Visualisation graphique        |
| ngrok       | Tunnel réseau                  |
| Wokwi       | Simulation ESP32               |

---

## Installation des dépendances

### Fichier requirements.txt

```txt
Flask
Flask-SocketIO
eventlet
```

---

### Installation

Dans le terminal :

```bash
pip install -r requirements.txt
```

---

### Alternative

```bash
pip install flask flask-socketio eventlet
```

---

## Lancement du projet

### 1. Lancer le serveur Flask

```bash
python server.py
```

Résultat attendu :

```text
Running on http://127.0.0.1:5000
```

---

### 🔹 2. Lancer ngrok

```bash
ngrok http 5000
ou
ngrok http 5000 --scheme=http
```

Exemple de lien généré :

```text
https://xxxxx.ngrok-free.dev
```

---

### 3. Configurer ESP32 (Wokwi)

Modifier dans le code ESP32 :

```cpp
const char* serverName = "http://xxxxx.ngrok-free.dev/upload";
```

 Remplacer par votre lien ngrok

---

###  4. Lancer la simulation Wokwi

* Cliquer sur ▶️ Run

Résultat attendu :

```text
Code réponse: 200
```

---

### 5. Accéder au dashboard

Dans le navigateur :

```text
http://127.0.0.1:5000
```

ou

```text
http://192.168.X.X:5000
```

---

## Tests réalisés

### ✔ Test 1 : Connexion WiFi

* ESP32 connecté au réseau Wokwi
* Résultat : OK

### ✔ Test 2 : Lecture capteur

* Température et humidité lues correctement
* Résultat : OK

### ✔ Test 3 : Envoi HTTP

* Code réponse 200
* Résultat : OK

### ✔ Test 4 : Backend Flask

* Réception et affichage des données
* Résultat : OK

### ✔ Test 5 : Dashboard

* Mise à jour en temps réel
* Graphique dynamique fonctionnel
* Résultat : OK

---

## Test alternatif (sans ESP32)

Simulation des données :

```powershell
Invoke-RestMethod -Uri http://127.0.0.1:5000/upload -Method POST -Body '{"temperature":30,"humidity":70}' -ContentType "application/json"
```

---

## Difficultés rencontrées

* Impossibilité pour Wokwi d’accéder aux adresses IP locales
* Solution : utilisation de ngrok
* Problèmes de synchronisation Socket.IO

---

## Choix techniques

* Flask : léger et adapté aux API IoT
* Socket.IO : communication temps réel efficace
* Chart.js : visualisation simple et dynamique
* ngrok : accès externe rapide et pratique

---

## 🚀 Résultat final

* Transmission des données en temps réel
* Dashboard interactif
* Architecture IoT complète fonctionnelle

---

## Améliorations possibles

* Ajout d’un contrôle LED (ON/OFF)
* Intégration d’une base de données
* Interface utilisateur améliorée
* Déploiement sur serveur cloud

---

## Conclusion

Ce projet met en œuvre une architecture IoT complète allant de l’acquisition des données jusqu’à leur visualisation en temps réel. Il démontre l’intégration de technologies web modernes pour la supervision de capteurs connectés.

---

 *Projet réalisé dans le cadre de l’examen IoT – Master 1 Intelligence Artificielle*
