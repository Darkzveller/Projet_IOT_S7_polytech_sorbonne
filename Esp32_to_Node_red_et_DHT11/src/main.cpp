#include <Arduino.h>
#include "WiFi.h"
#include <HTTPClient.h>
#include "DHT.h"
// Capteur de temperature et d'humidite DHT11
// https://tutoduino.fr/
// Copyleft 2020
#include "DHT.h"
// Definit la broche de l'Arduino sur laquelle la 
// broche DATA du capteur est reliee 
#define DHTPIN 4
// Definit le type de capteur utilise
#define DHTTYPE DHT11
// Declare un objet de type DHT
// Il faut passer en parametre du constructeur 
// de l'objet la broche et le type de capteur
DHT dht(DHTPIN, DHTTYPE);

#define MON_TELEPHONE
// #define MA_FREEBOX

const char *name_card_elec = "esp32_test_node_red_v2"; // Nom d'hôte de la carte ESP32
// BESOIN DE ME SIMPLIFIER MA VIE
#ifdef MON_TELEPHONE
const char *ssid = "Me voici";      // SSID du réseau WiFi
const char *password = "youssef13"; // Mot de passe du réseau WiFi
String serverName = "http://192.168.238.171:1880/donnes";
#endif
#ifdef MA_FREEBOX                                // Nom d'hôte de la carte ESP32
const char *ssid = "Freebox-10E503";             // SSID du réseau WiFi
const char *password = "h2nn5qzkvfq639rfqv5s2v"; // Mot de passe du réseau WiFi
String serverName = "http://192.168.1.110:1880/donnes";
#endif



void setup()
{
  Serial.begin(9600);
  dht.begin();

  // Définit le nom d'hôte pour la carte ESP32 sur le réseau
  WiFi.setHostname(name_card_elec);
  // Passe le WiFi en mode station (client du réseau WiFi)
  WiFi.mode(WIFI_STA);

  // Démarre la connexion WiFi avec les identifiants donnés
  WiFi.begin(ssid, password);
  Serial.println();
  Serial.print("SSID : ");
  Serial.println(ssid);

  Serial.println("Connexion au WiFi en cours...");

  // Boucle jusqu'à ce que la connexion au WiFi soit réussie
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    Serial.println("Connection Failed! Rebooting...");
    delay(1000);
    // Redémarrage si la connexion échoue (commenté pour l'instant)
    ESP.restart();
  }

  Serial.print("Adresse IP ESP32 : ");
  Serial.println(WiFi.localIP());

  // Affiche le succès de la connexion
  Serial.println("");
  Serial.println("Connexion établie !");
}

void loop()
{

  static int compteur = 0;
    compteur++;

  float humidite = dht.readTemperature();
  float temperature = dht.readHumidity();

  Serial.println("Temperature = " + String(humidite)+" °C");
  Serial.println("Humidite = " + String(temperature)+" %");




  Serial.print("Compteur : ");
  Serial.println(compteur);

  Serial.print("Humidite : ");
  Serial.print(humidite, 1);
  Serial.println(" %");

  Serial.print("Temperature : ");
  Serial.print(temperature, 1);
  Serial.println(" °C");

  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;

    http.begin(serverName.c_str());
    http.addHeader(
      "Content-Type",
      "application/x-www-form-urlencoded"
    );

    // Toutes les données sont envoyées dans une seule requête
    String httpRequestData =
      "compteur=" + String(compteur) +
      "&hum=" + String(humidite, 1) +
      "&temp=" + String(temperature, 1);

    Serial.print("Donnees envoyees : ");
    Serial.println(httpRequestData);

    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0)
    {
      Serial.print("Code HTTP : ");
      Serial.println(httpResponseCode);

      String reponse = http.getString();
      Serial.print("Reponse Node-RED : ");
      Serial.println(reponse);
    }
    else
    {
      Serial.print("Erreur HTTP : ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }
  else
  {
    Serial.println("Wi-Fi deconnecte");
  }
  delay(1000);
}