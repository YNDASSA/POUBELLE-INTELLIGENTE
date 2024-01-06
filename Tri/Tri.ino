#include <Servo.h>

// Constantes pour les broches des capteurs et actionneurs
const int capteurPlastiquePin = 2;
const int capteurPapierPin = 3;
const int capteurVerrePin = 4;
const int servomoteurPlastiquePin = 5;
const int servomoteurPapierPin = 6;
const int servomoteurVerrePin = 7;

// Variables pour stocker les états des capteurs
int etatCapteurPlastique = 0;
int etatCapteurPapier = 0;
int etatCapteurVerre = 0;

// Objets pour contrôler les servomoteurs
Servo servomoteurPlastique;
Servo servomoteurPapier;
Servo servomoteurVerre;

void setup() {
  // Initialisation des broches des capteurs en entrée
  pinMode(capteurPlastiquePin, INPUT);
  pinMode(capteurPapierPin, INPUT);
  pinMode(capteurVerrePin, INPUT);

  // Attache des servomoteurs aux broches correspondantes
  servomoteurPlastique.attach(servomoteurPlastiquePin);
  servomoteurPapier.attach(servomoteurPapierPin);
  servomoteurVerre.attach(servomoteurVerrePin);
}

void loop() {
  // Lecture des états des capteurs
  etatCapteurPlastique = digitalRead(capteurPlastiquePin);
  etatCapteurPapier = digitalRead(capteurPapierPin);
  etatCapteurVerre = digitalRead(capteurVerrePin);

  // Vérification des capteurs et activation des servomoteurs appropriés
  if (etatCapteurPlastique == HIGH) {
    ouvrirServomoteur(servomoteurPlastique);
  } else {
    fermerServomoteur(servomoteurPlastique);
  }

  if (etatCapteurPapier == HIGH) {
    ouvrirServomoteur(servomoteurPapier);
  } else {
    fermerServomoteur(servomoteurPapier);
  }

  if (etatCapteurVerre == HIGH) {
    ouvrirServomoteur(servomoteurVerre);
  } else {
    fermerServomoteur(servomoteurVerre);
  }
}

// Fonction pour ouvrir un servomoteur
void ouvrirServomoteur(Servo servo) {
  servo.write(90); // Angle d'ouverture souhaité
}

// Fonction pour fermer un servomoteur
void fermerServomoteur(Servo servo) {
  servo.write(0); // Angle de fermeture souhaité
}
