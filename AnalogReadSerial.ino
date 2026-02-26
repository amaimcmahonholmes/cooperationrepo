/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/AnalogReadSerial/
*/
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
      lcd.begin(16, 2);

    lcd.setRGB(colorR, colorG, colorB);

  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
      lcd.setCursor(0, 1);
      lcd.print("Temp: ");
      lcd.print(sensorValue);
   
    // print the number of seconds since reset:
    // lcd.print(millis() / 10);

    delay(5);

  //lcd.print(sensorValue);
  delay(10);  // delay in between reads for stability
}
