#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

void setup() {
  Wire.begin(17, 18);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, heart);
  lcd.setCursor(0,0);
  lcd.print("Hello World :3");
  lcd.setCursor(0,1);
  lcd.print("(^ w ^) ");
  lcd.write(byte(0));
  lcd.write(' ');
  lcd.write(byte(0));
  lcd.write(' ');
  lcd.write(byte(0));

}

void loop() {}