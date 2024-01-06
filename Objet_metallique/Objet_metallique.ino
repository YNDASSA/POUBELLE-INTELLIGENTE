#include <Servo.h>

int Ledrouge = 3;
int Magnetiquepin_num = 2;
bool Detectionmagnetique;

Servo monServo;
int pinServo = 9;

void setup () {
  pinMode(Ledrouge, OUTPUT);
  pinMode(Magnetiquepin_num, INPUT);
  monServo.attach(pinServo);
}

void loop () {
  Detectionmagnetique = digitalRead(Magnetiquepin_num);
  
  if (Detectionmagnetique == HIGH) {
    monServo.write(90); // Angle à 90 degrés pour ouvrir la trappe
  } else {
    monServo.write(0); // Angle à 0 degré pour fermer la trappe
  }
  
  delay(500);
}