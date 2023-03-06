#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*--- LCD ---*/
LiquidCrystal_I2C lcd(0x27,16,2);  // Création de l'objet lcd

unsigned long previousMillis = 0;
int temps = 20;

void setup() {
  // put your setup code here, to run once:
    /*--- Initialisation de l'écran ---*/
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:


  unsigned long currentMillis = millis();
  /*---------- Timer ----------*/
  if (currentMillis - previousMillis > 1000){
    previousMillis = currentMillis;
    temps--;
  }

  lcd.clear();
  lcd.print(temps);
  delay(20);
  
}
