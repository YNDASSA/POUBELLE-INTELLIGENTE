#include <Servo.h>
#include "poubelleUtils.h"

Servo servo;
int trigPin = 5;
int echoPin = 6;
int servoPin = 7;
int led = 10;
long duration, dist, average;
long aver[3]; // tableau pour la moyenne
bool presenceDetected = false; // Variable pour indiquer si une présence est détectée

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT); // Ajout du mode de la LED en sortie
  servo.write(0); // fermer le capuchon à l'allumage
  delay(100);   // durée d'ouverture de la poubelle
  servo.detach();
}

void measure() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  dist = (duration / 2) / 29.1; // obtenir la distance
}

void loop() {
  // Ouverture et fermeture de la poubelle
  for (int i = 0; i <= 2; i++) { // distance moyenne
    measure();
    aver[i] = dist;
    delay(10); // délai entre les mesures
  }
  dist = (aver[0] + aver[1] + aver[2]) / 3;

  if (dist < 50) {
    presenceDetected = true; // Présence détectée
  }

  if (presenceDetected) {
    // Vérifier si la poubelle est pleine
    if (isFull) {
      // Verrouillage de la poubelle
      digitalWrite(trigPin, LOW);
    } else {
      servo.attach(servoPin);
      digitalWrite(led, HIGH);
      delay(1);
      servo.write(0);
      delay(5000);
      servo.write(150);
      delay(1000);
      digitalWrite(led, LOW);
      servo.detach();
      presenceDetected = false; // Réinitialiser la variable de détection de présence
    }
  }
  
  Serial.println(dist); // Changer Serial.print en Serial.println pour afficher chaque valeur de distance sur une nouvelle ligne
}
