// #include <Arduino.h>

// int DHpin = 4;
// byte dat[5];
// byte read_data()
// {
//     byte data;
//     for (int i = 0; i < 8; i++)
//     {
//         if (digitalRead(DHpin) == LOW)
//         {
//             while (digitalRead(DHpin) == LOW)
//                 ;
//             delayMicroseconds(30);
//             if (digitalRead(DHpin) == HIGH)
//                 data |= (1 << (7 - i));
//             while (digitalRead(DHpin) == HIGH)
//                 ;
//         }
//     }
//     return data;
// }
// void start_test()
// {
//     digitalWrite(DHpin, LOW);
//     delay(30);
//     digitalWrite(DHpin, HIGH);
//     delayMicroseconds(40);
//     pinMode(DHpin, INPUT);
//     while (digitalRead(DHpin) == HIGH)
//         ;
//     delayMicroseconds(80);
//     if (digitalRead(DHpin) == LOW)
//         ;
//     delayMicroseconds(80);
//     for (int i = 0; i < 4; i++)
//         dat[i] = read_data();
//     pinMode(DHpin, OUTPUT);
//     digitalWrite(DHpin, HIGH);
// }
// void setup()
// {
//     Serial.begin(9600);
//     pinMode(DHpin, OUTPUT);
// }
// void loop()
// {
//     start_test();
//     Serial.print("Current humdity =");
//     Serial.print(dat[0], DEC);
//     Serial.print('.');
//     Serial.print(dat[1], DEC);
//     Serial.println('%');
//     Serial.print("Current temperature =");
//     Serial.print(dat[2], DEC);
//     Serial.print('.');
//     Serial.print(dat[3], DEC);
//     Serial.println('C');
//     delay(1000);
// }

#include <Arduino.h>
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
void setup() {
  Serial.begin(9600);
  
  // Initialise la capteur DHT11
  dht.begin();
}
void loop() {
  // Recupere la temperature et l'humidite du capteur et l'affiche
  // sur le moniteur serie
  Serial.println("Temperature = " + String(dht.readTemperature())+" °C");
  Serial.println("Humidite = " + String(dht.readHumidity())+" %");
  // Attend 10 secondes avant de reboucler
  delay(10000);
}
