#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

unsigned long startTime = 0;
bool resetTriggered = false;

void setup() {
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  Serial.begin(9600);
}

void loop() {

  int sensorValue = analogRead(A0);
  int analogValue = analogRead(A1);

  if (analogValue >= 500 && !resetTriggered) {
    startTime = millis();
    resetTriggered = true;
  }

  if (analogValue < 500) {
    resetTriggered = false;
  }

  unsigned long elapsed = (millis() - startTime) / 1000;

  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(elapsed);
  lcd.print("s     ");  

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(sensorValue);
  lcd.print("     ");

  delay(200);
}