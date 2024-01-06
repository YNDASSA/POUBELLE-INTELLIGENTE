#include <Servo.h>

// Objets pour contrôler les servomoteurs
Servo servomoteurPlastique;
Servo servomoteurMagnetique;
Servo servomoteur;
Servo servo;

const int capteurPlastiquePin = 2;
const int capteurMagnetiquePin = 3;

int buzzerPin = 4;

int trigPin = 5;
int echoPin = 6;
int servoPin = 7;

const int servomoteurPlastiquePin = 8;
const int servomoteurMagnetiquePin = 9;

const int servomoteurPin = 14;// vérifier si cette broche existe ou est disponible sur la carte arduino

int blueLed = 10;
int yellowLed = 11;
int greedLed = 12;
int redLed = 13;

// Variables pour stocker les états des capteurs
int etatCapteurPlastique = 0;
int etatCapteurMagnetique = 0;

long duration, dist, average;
long aver[3]; // tableau pour la moyenne

bool presenceDetected = false; // Variable pour indiquer si une présence est détectée

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  servomoteurPlastique.attach(servomoteurPlastiquePin);
  servomoteurMagnetique.attach(servomoteurMagnetiquePin);
  servomoteur.attach(servomoteurPin);
  pinMode(capteurPlastiquePin, INPUT);
  pinMode(capteurMagnetiquePin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greedLed, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  servo.write(0);
  delay(100);
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
  dist = (duration / 2) / 29.1;
}

// Fonction pour ouvrir un servomoteur
void ouvrirServomoteur(Servo servo) {
  servo.write(150); // Angle d'ouverture souhaité
  delay(1000);
}

// Fonction pour fermer un servomoteur
void fermerServomoteur(Servo servo) {
  servo.write(0); // Angle de fermeture souhaité
}

void loop() {

  // Ouverture et fermeture automatique de la poubelle

  for (int i = 0; i <= 2; i++) {
    measure();
    aver[i] = dist;
    delay(10);
  }

  dist = (aver[0] + aver[1] + aver[2]) / 3;

  if (dist < 50) {
    presenceDetected = true;
  }

  if (presenceDetected) {
    servo.attach(servoPin);
    digitalWrite(blueLed, HIGH);
    delay(1);
    servo.write(0);
    delay(5000);
    servo.write(150);
    delay(1000);
    digitalWrite(blueLed, LOW);
    servo.detach();
    presenceDetected = false;
  }

  // Tri sélectif

  // Lecture des états des capteurs
  etatCapteurPlastique = digitalRead(capteurPlastiquePin);
  etatCapteurMagnetique = digitalRead(capteurMagnetiquePin);

  // Vérification des capteurs et activation des servomoteurs appropriés
  //On vérifie d'abord si les capteurs magnétique et plastique ont détecté l'objet et l'entrainer dans le compartiment correspondant
  
  if (etatCapteurPlastique == HIGH || etatCapteurMagnetique == HIGH) {
    if (etatCapteurPlastique == HIGH) {
      ouvrirServomoteur(servomoteurPlastique);
    } else {
      fermerServomoteur(servomoteurPlastique);
    }

    if (etatCapteurMagnetique == HIGH) {
      ouvrirServomoteur(servomoteurMagnetique);
    } else {
      fermerServomoteur(servomoteurMagnetique);
    }

    //Si l'objet n'est pas détecté plus haut, il sera redirigé vers le compartiment par défaut 
  } else {
    ouvrirServomoteur(servomoteur);
    delay(7000);
    fermerServomoteur(servomoteur);
  }
}
