/*
  Fixed & Optimized Version
*/

#define BLYNK_TEMPLATE_ID "TMPL4YeD_p0Ei"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "U3R_65SJoZQ7neM7CK83u3a-bz8IWT68"
#define LED_PIN 13

#define BLYNK_PRINT Serial

#include <SPI.h>
#include <WiFi.h>
#include <BlynkSimpleWifi.h>
#include <ArduinoJson.h>
#include "arduino_secrets.h"

#include <Wire.h>
#include <math.h>
#include "rgb_lcd.h"

// WiFi
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
WidgetLED led1(V1);

BlynkTimer timer;

// LCD
rgb_lcd lcd;
const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

// Thermistor constants
const int B = 3975;
const int R0 = 100000;   // MUST match your hardware

// Pins
#define LED_PIN 3

// Blynk

// Timer + button logic
unsigned long startTime = 0;
bool resetTriggered = false;

// LED state
bool ledState = false;

/* ---------------- BLYNK ---------------- */

BLYNK_WRITE(V0)
{
  int value = param.asInt();
  Blynk.virtualWrite(V0, value);
  digitalWrite(13, value);  
}

 BLYNK_CONNECTED()
{
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made"); 
}

/* ---------------- FUNCTIONS ---------------- */
// Blink LED without blocking
void blinkLED() 
{
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
}

// void myTimerEvent()
// {
//   // You can send any value at any time.
//   // Please don't send more that 10 values per second.
//   Blynk.virtualWrite(V2, millis() / 1000);
  
// }
void readSensorAndDisplay() {

  int sensorValue = analogRead(A0);  // temperature
  int analogValue = analogRead(A1);  // button

  // Button logic (start/reset timer)
  if (analogValue >= 500 && !resetTriggered) {
    startTime = millis();
    resetTriggered = true;
  }

  if (analogValue < 500) {
    resetTriggered = false;
  }

  unsigned long elapsed = (millis() - startTime) / 1000;

  // Thermistor calculation (FIXED)
  float resistance = (float)(1023 - sensorValue) * R0 / sensorValue;
  float temperature = 1 / (log(resistance / R0) / B + 1 / 298.15) - 273.15;

  // LCD display
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.print(elapsed);
  lcd.print("s     ");

  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print((char)223);
  lcd.print("C     ");

  // Serial debug
  Serial.print("Temp = ");
  Serial.println(temperature);
  Serial.println(resistance);
  
  Blynk.virtualWrite(V4,temperature);


}

/* ---------------- SETUP ---------------- */

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);

  lcd.begin(16, 2);
  lcd.setRGB(colorR, colorG, colorB);

  // Connect to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Timers
  timer.setInterval(500L, readSensorAndDisplay); // sensor + LCD
  timer.setInterval(1000L, blinkLED);            // LED blink

  // timer.setInterval(1000L, myTimerEvent);

}
 BLYNK_WRITE(V5){
  int value = param.asInt();

  if (value == 1 ) {
  digitalWrite(3, HIGH);  // turn the LED on (HIGH is the voltage level)
  lcd.setRGB(0,255,0);
  }
  else {
  digitalWrite(3, LOW);   // turn the LED off by making the voltage LOW
  lcd.setRGB(255,0,0);
  }
 }



/* ---------------- LOOP ---------------- */

void loop() {
  Blynk.run();
  timer.run();
}