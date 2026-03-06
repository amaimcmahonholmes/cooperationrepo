/*
  This example code is in the public domain.
  We used the 'AnalogReadSerial' for some parts of the code as a small base.

  Modified by Aoife McMahon Holmes on 06/03/2026
*/

#include <Wire.h>
#include "rgb_lcd.h"

//We will add <Wifi.h> when we begin fully working on our internet component

//getting lcd screen colour
rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

//startTime is for the timer while resetTrigger is for if the button component is pushed or not
unsigned long startTime = 0;
bool resetTriggered = false;

void setup() {
  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);
  Serial.begin(9600);
}

void loop() {
//the sensorValue is for the temperature sensor while the analogValue is for the 
  int sensorValue = analogRead(A0);
  int analogValue = analogRead(A1);

//if button clicked
  if (analogValue >= 500 && !resetTriggered) {
    startTime = millis();
    resetTriggered = true;
  }
//if button isn't clicked
  if (analogValue < 500) {
    resetTriggered = false;
  }
  
//elapsed is converting milliseconds into seconds for the timer
  unsigned long elapsed = (millis() - startTime) / 1000;

//formating the LCD screen
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(elapsed);
  lcd.print("s     ");  

//lcd.setCursor is used to have Temp display on a different line from the Time

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(sensorValue);
  lcd.print("     ");

  delay(200);
}