#include <Servo.h>

/*--- SERVOS MOUVEMENTS ---*/
Servo ServoX;        // Création objet servo pour le mouvement en X
Servo ServoY;        // Création objet servo pour le mouvement en Y

//const int posIniX = 70; // Indique la position initiale du servoX
//const int posIniY = 95;   // Indique la position initiale du servoY

const int posIniX = 90; // Indique la position initiale du servoX
const int posIniY = 91;   // Indique la position initiale du servoY

const int pinServoX = 6; // Pin de branchement du servoX
const int pinServoY = 5; // Pin de branchement du servoY

/*--- JOYSTICK ---*/
const int joyX = 2;    //Pin de branchement du joystick (axe X)
const int joyY = 3;    //Pin de branchement du joystick (axe Y)

void setup() {
  // put your setup code here, to run once:
  /*--- Initialisation des servos pour les mouvements ---*/
  ServoX.attach(pinServoX);
  ServoX.write(posIniX);
  
  ServoY.attach(pinServoY);
  ServoY.write(posIniY);

  Serial.begin(9600);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  /*---------- Contrôle de la partie ----------*/
  int valX = analogRead(joyX);    // Valeur en X du joystick
  int valY = analogRead(joyY);    // Valeur en X du joystick

  // Conversion des valeurs en des valeurs entre 10 et 170
  //valX = map(valX, 0, 1023, 10, 170);
  //valY = map(valY, 0, 1023, 10, 170);

  valX = map(valX, 0, 1023, 170, 10);
  valY = map(valY, 0, 1023, 170, 10);

  Serial.print("X: ");
  Serial.print(valX);
  Serial.print(" Y: ");
  Serial.println(valY);

  ServoX.write(valX);
  ServoY.write(valY);  
 

  delay(5);
}
