#include <Arduino.h>

#define LED 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(/* baud rate */115200);
  pinMode(/* pin */ LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  Serial.println("High");
  delay(/* ms */ 2000);
  digitalWrite(LED, LOW);
  Serial.println("Low");
  delay(/* ms */ 2000);
}