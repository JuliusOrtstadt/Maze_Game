/*--- BOUTON ---*/
const int bouton = 4; // Pin Bouton

void setup() {
  // put your setup code here, to run once:
  /*--- Définition mode du pin pour le bouton ---*/
  pinMode(bouton, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(bouton) == HIGH){
    Serial.println("Button pressed");
  }
  else{
    Serial.println("Button not pressed");
  }
  delay(1000);
}
