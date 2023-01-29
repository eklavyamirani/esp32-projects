#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BAUD_RATE 115200
#define SEA_LEVEL_PRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C. @todo read https://randomnerdtutorials.com/esp32-i2c-communication-arduino-ide/
TwoWire I2CBME = TwoWire(0);
TwoWire I2CDisplay = TwoWire(1);

// display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &I2CDisplay, -1);

unsigned long delayTime;

void findAddress();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(/* baud rate */ BAUD_RATE);
  Serial.println("Starting display");
  I2CDisplay.setPins(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("Couldn't find display");
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  Serial.println("Display ready");

  Serial.println("BME 280 test");

  bool status;

  // Switch to different pins
  I2CBME.setPins(/*sda*/ 27, /*scl*/ 25);
  status = bme.begin(119U, &I2CBME); // @todo what is this?
  if (!status)
  {
    Serial.println("Couldn't find BME 280");
    while(1);
  }

  Serial.println("BME test done");
  Serial.println();

  delayTime = 1000;
}

void findAddress()
{
  Serial.println("Looking for devices");
  byte error;
  for (int address = 0; address < 127; ++address)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.printf("Device found at %04x \n", address);
    }
  }
}

void printValues() {  
  // Convert temperature to Fahrenheit
  Serial.print("Temperature = ");
  Serial.print(1.8 * bme.readTemperature() + 32);
  Serial.println(" *F");
  
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEA_LEVEL_PRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
}

void redrawDisplay() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  // Convert temperature to Fahrenheit
  double temp = 1.8 * bme.readTemperature() + 32;
  display.printf("T: %.1f *F", temp);
  Serial.printf("T: %.1f *F\n", temp);
  display.setCursor(0, 30);
  
  // Serial.print("Pressure = ");
  // Serial.print(bme.readPressure() / 100.0F);
  // Serial.println(" hPa");

  double humidity = bme.readHumidity();
  display.printf("P: %.1f %%", humidity);
  Serial.printf("P: %.1f %%\n", humidity);

  // Serial.print("Approx. Altitude = ");
  // Serial.print(bme.readAltitude(SEA_LEVEL_PRESSURE_HPA));
  // Serial.println(" m");

  // Serial.print("Humidity = ");
  // Serial.print(bme.readHumidity());
  // Serial.println(" %");

  display.display();
}

void loop() { 
  printValues();
  redrawDisplay();
  delay(delayTime);
}