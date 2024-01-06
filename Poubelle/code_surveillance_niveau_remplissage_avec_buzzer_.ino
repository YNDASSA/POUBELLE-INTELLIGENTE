#include <Servo.h>

Servo servo;
int trigPin = 5;
int echoPin = 6;
int servoPin = 7;
int redLed = 10;
int yellowLed = 11;
int greenLed = 12;
int blueLed = 13;
int buzzerPin = 9; // Ajout de la déclaration pour la broche du buzzer
long duree, dist, moyenne;
long moyennes[3];
bool isFull = false;

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(buzzerPin, OUTPUT); // Définir la broche du buzzer en tant que sortie
  pinMode(echoPin, INPUT);
  servo.write(0);
  delay(100);
  servo.detach();
}

void mesure() {
  digitalWrite(blueLed, HIGH);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duree = pulseIn(echoPin, HIGH);
  dist = (duree / 2) / 29.1;
}

void loop() {
  for (int i = 0; i <= 2; i++) {
    mesure();
    moyennes[i] = dist;
    delay(10);
  }

  dist = (moyennes[0] + moyennes[1] + moyennes[2]) / 3;

  if (dist <= 15) {
    isFull = true;
    servo.attach(servoPin);
    digitalWrite(redLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, LOW);
    digitalWrite(buzzerPin, HIGH); // Activer le buzzer pour émettre un son
    servo.detach();
  } else if (dist >= 16 && dist <= 85) {
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(greenLed, LOW);
    digitalWrite(buzzerPin, LOW); // Désactiver le buzzer
  } else {
    digitalWrite(redLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(greenLed, HIGH);
    digitalWrite(buzzerPin, LOW); // Désactiver le buzzer
  }
}
