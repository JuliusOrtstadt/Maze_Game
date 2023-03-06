#include <Servo.h>

/*--- SERVO PORTE ---*/
Servo Servo_Porte;          // Création d'un objet servo
int posIni = 160;              // Sauvegarde de la position initiale du servo
int pinServoPorte = 9;       // Pin de branchement du servo

void setup() {
  // put your setup code here, to run once:
  /*--- Initialisation du servo porte ---*/
  Servo_Porte.attach(pinServoPorte);
  Servo_Porte.write(posIni);
}

void loop() {
  // put your main code here, to run repeatedly:
  Servo_Porte.write(posIni);

  delay(2000);
  
  Servo_Porte.write(70);

  delay(2000);


}
