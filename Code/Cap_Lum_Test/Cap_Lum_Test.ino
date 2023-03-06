/*--- CAPTEURS DETECTION ---*/
const int detecPerd = 10;   // Pin de branchement pour le détecteur perdant
const int detecGagn = 11;   // Pin de branchement pour le détecteur gagant


void setup() {
  // put your setup code here, to run once:
    /*--- Initialisation des capteurs pour la bille ---*/
  pinMode(detecPerd, INPUT);
  pinMode(detecGagn, INPUT);


  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(detecPerd) == LOW){
    Serial.println("LOST");
  }

  if (digitalRead(detecGagn) == LOW){
    Serial.println("WIN");
  }
}
