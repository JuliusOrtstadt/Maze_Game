
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

/*--- LCD ---*/
LiquidCrystal_I2C lcd(0x27,16,2);  // Création de l'objet lcd


void setup() {
  // put your setup code here, to run once:
  /*--- Initialisation de l'écran ---*/
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.print("hello World");

  delay(5000);
}
