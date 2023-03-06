
/*--- LED ---*/
const int LED_O = 3; // Pin LED Orange
const int LED_V = 2; // Pin LED Verte

void setup() {
  // put your setup code here, to run once:
  /*--- Définition mode du pin pour les led ---*/
  pinMode(LED_O, OUTPUT);
  pinMode(LED_V, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_O, HIGH);
  digitalWrite(LED_V, LOW);
  Serial.println("Green on");
  delay(2000);

  digitalWrite(LED_O, LOW);
  digitalWrite(LED_V, HIGH);
  Serial.println("Orange on");

  delay(2000);
  
}
