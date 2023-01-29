#include <ESP32Servo.h>
#include <Arduino.h>

Servo servo;
int pos = 0;

void setup() {
  // put your setup code here, to run once:
  	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	Serial.begin(115200);
	servo.setPeriodHertz(50);      // Standard 50hz servo

  servo.attach(/*pin*/ 14);
}

void loop() {
  // put your main code here, to run repeatedly:
  int direction = 1;
  for (int pos = 0; pos <= 180;++pos)
  {
    servo.write(pos);
    delay(100);
  }

  delay(1000);

  for (int pos = 180; pos >= 0;--pos)
  {
    servo.write(pos);
    delay(100);
  }
}