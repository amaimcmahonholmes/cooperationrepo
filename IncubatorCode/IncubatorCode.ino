/*
  This example code is in the public domain.
  We used the 'AnalogReadSerial' for some parts of the code as a small base.

  Modified by Eva conlon on 24/02/2026
  Modified by Aoife McMahon Holmes on 06/03/2026
*/
// #include <WiFiS3.h>
// #include <ArduinoJson.h>
// #include "arduino_secrets.h" 
// char ssid[] = SECRET_SSID;        // your network SSID (name)
// char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
// int status = WL_IDLE_STATUS;     // the WiFi radio's status


#include <Wire.h>
#include <math.h>
#include "rgb_lcd.h"

//We will add <Wifi.h> when we begin fully working on our internet component

//getting lcd screen colour
rgb_lcd lcd;

#if defined(ARDUINO_ARCH_AVR)
#define debug  Serial
#elif defined(ARDUINO_ARCH_SAMD) ||  defined(ARDUINO_ARCH_SAM)
#define debug  SerialUSB
#else
#define debug  Serial
#endif

const int B = 4275000;
const int R0 = 100000;       


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

  // // check for the WiFi module:
  // if (WiFi.status() == WL_NO_MODULE) {
  //   Serial.println("Communication with WiFi module failed!");
  //   // don't continue
  //   while (true);
  // }
  // // you're connected now, so print out the data:
  // Serial.print("You're connected to the network");
  // printCurrentNet();
  // printWifiData();

}

void loop() {
//     // check the network connection once every 10 seconds:
//  lcd.setCursor(0, 1);
//  lcd.print(millis() / 1000);

//   delay(10000);
//   printCurrentNet();
//   printWifiData();

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
// <<<<<<< Updated upstream:IncubatorCode/IncubatorCode.ino
  
//elapsed is converting milliseconds into seconds for the timer
  unsigned long elapsed = (millis() - startTime) / 1000;

//formating the LCD screen
// =======

  // unsigned long elapsed = (millis() - startTime) / 1000;

  float resistance = (float)(1023-sensorValue)*10000/sensorValue;
  float temperature = 1/(log(resistance/10000)/B+1/298.15)-273.15;

  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(elapsed);
  lcd.print("s     ");  

//lcd.setCursor is used to have Temp display on a different line from the Time

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(char(223));
  lcd.write("C");
  lcd.print("     ");
  

  Serial.print("temperature = ");
  Serial.println(temperature);
  Serial.println(sensorValue);
  Serial.println(R0);

  delay(200);
}
