/*--- ORTSTADT Julius G4 Peip2 - Projet Maze_Game ---*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

/*--- Etat du jeu ---*/
bool game = false;

/*--- Timer -> Score ---*/
unsigned long previousMillis = 0; // État de millis avant

/*--- LED ---*/
const int LED_V = 2;      // Pin LED Verte
const int LED_O = 3;      // Pin LED Orange

/*--- BOUTON ---*/
const int bouton = 4;     // Pin bouton
bool bouton_app = false;  // Statut du bouton

/*--- LCD ---*/
LiquidCrystal_I2C lcd(0x27,16,2);  // Création de l'objet lcd

/*--- JOYSTICK ---*/
const int joyX = 2;    //Pin de branchement du joystick (axe X)
const int joyY = 3;    //Pin de branchement du joystick (axe Y)

/*--- SERVOS MOUVEMENTS ---*/
Servo ServoX;        // Création objet servo pour le mouvement en X
Servo ServoY;        // Création objet servo pour le mouvement en Y

const int posIniX = 90 ;    // Indique la position initiale du servoX
const int posIniY = 91;     // Indique la position initiale du servoY

const int pinServoX = 6;    // Pin de branchement du servoX
const int pinServoY = 5;    // Pin de branchement du servoY

/*--- SERVO PORTE ---*/
Servo ServoPorte;           // Création d'un objet servo
int posIniPorte = 160;      // Sauvegarde de la position initiale du servo
int pinServoPorte = 9;      // Pin de branchement du servo

/*--- CAPTEURS DETECTION ---*/
const int detecPerd = 10;   // Pin de branchement pour le détecteur perdant
const int detecGagn = 11;   // Pin de branchement pour le détecteur gagant

void setup() {
  /*--- Définition mode du pin pour les led ---*/
  pinMode(LED_O, OUTPUT);
  pinMode(LED_V, OUTPUT);

  digitalWrite(LED_V, HIGH);  // LED verte éteinte
  digitalWrite(LED_O, LOW);   // LED orange allumée
  
  /*--- Définition mode du pin pour le bouton ---*/
  pinMode(bouton, OUTPUT);

  /*--- Initialisation de l'écran ---*/
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Bienvenue !");
  lcd.setCursor(0,1);
  lcd.print("Maze Game");
  
  /*--- Initialisation du servo porte ---*/
  ServoPorte.attach(pinServoPorte);
  ServoPorte.write(posIniPorte);

  /*--- Initialisation des servos pour les mouvements ---*/
  ServoX.attach(pinServoX);
  ServoX.write(posIniX);
  
  ServoY.attach(pinServoY);
  ServoY.write(posIniY);
  
  /*--- Initialisation des capteurs pour la bille ---*/
  pinMode(detecPerd, INPUT);
  pinMode(detecGagn, INPUT);
  
  /*--- Initialisation de la connexion série ---*/
  Serial.begin(9600);

  /*--- Delay initial ---*/
  delay(5000);
}

/*--- Fonction pour afficher les messages sur l'écran ---*/
void lcd_msg (String c, int i, int j){
  lcd.setCursor(i,j);
  lcd.print(c);
}

void loop() {
  // put your main code here, to run repeatedly:
  int score = 0;          // Score du joueur -> temps mis pour gagner
  int countdown = 4;      // Compteur pour démarrer la partie
   
  lcd.clear();
  lcd_msg("Valider pour",0,0);
  lcd_msg("jouer",0,1);

  delay(20);
  
  if (digitalRead(bouton) == HIGH){
    bouton_app = true;
    
    lcd.clear();
    lcd_msg("Liberation de ",0,0);
    lcd_msg("la bille",0,1);
    delay(2000);
    
    ServoPorte.write(70); // Ouverture de la porte pour la bille
    
    while(bouton_app == true){  
      lcd.clear();
      lcd_msg("Placer bille sur",0,0);    // Étapes à réalisés par le joueur
      lcd_msg("start et valider",0,1);
      
      delay(20);
      
      if (digitalRead(bouton) == HIGH){
        lcd.clear();

        /*--- Coutdown pour le début de la partie ---*/
        while (countdown != 0){
          unsigned long currentMillis = millis();       // État de millis actuel
          if (currentMillis - previousMillis > 1000){
            previousMillis = currentMillis;
            countdown--;
            lcd_msg("La partie debute",0,0);
            lcd_msg("dans " + String(countdown) + "s",0,1);
          }
        }
        digitalWrite(LED_V, LOW);
        digitalWrite(LED_O, HIGH);
        game = true;                // Début de la partie
        bouton_app = false;
      }
    }
    
    while (game == true){
      unsigned long currentMillis = millis();     // État de millis actuel
      /*---------- Timer ----------*/
      if (currentMillis - previousMillis > 1000){
        previousMillis = currentMillis;
        score++;
      }
      
      lcd.clear();
      lcd_msg("Score: " + String(score) + "s",0,0);         // Affichage du temps écoulé = score
      
      /*---------- Contrôle de la partie ----------*/
      int valX = analogRead(joyX);    // Valeur en X du joystick
      int valY = analogRead(joyY);    // Valeur en X du joystick

      // Conversion des valeurs en des valeurs entre 10 et 170
      valX = map(valX, 0, 1023, 170, 10);
      valY = map(valY, 0, 1023, 170, 10);

      // Application de ces valeurs sur les servos
      ServoX.write(valX);
      ServoY.write(valY);

      // Détection si le joueur perd
      if (digitalRead(detecPerd) == LOW){ // Bille détectée du côté gagnant
        digitalWrite(LED_V, HIGH);        // LED verte éteinte
        digitalWrite(LED_O, LOW);         // LED orange allumée
        
        lcd.clear();
        lcd_msg("Vous avez perdu!",0,0);
        
        delay(1500);
        ServoPorte.write(posIniPorte);  // Fermeture de la porte pour la bille
        game = false;                   // Arrêt de la partie
      }

      // Détection si le joueur gagne
      if (digitalRead(detecGagn) == LOW){ // Bille détectée du côté gagnant
        digitalWrite(LED_V, HIGH);        // LED verte éteinte
        digitalWrite(LED_O, LOW);         // LED orange allumée

        score = score - 1;                // Tolérance pour que la bille soit acheminée vers le capteur
        
        lcd.clear();
        lcd_msg("Vous avez gagne",0,0);
        lcd_msg("Score: " + String(score) + "s",0,1);

        delay(1500);
        ServoPorte.write(posIniPorte);  // Fermeture de la porte pour la bille
        delay(2000);
        game = false;                   // Arrêt de la partie
      }
      
      delay(5);
    } 
  } 
}
