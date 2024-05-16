// Project: Smart Plant Waterer
// Adib Hasan & Kyle Guo

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include <dht.h>

dht DHT;  // For DHT11 temperature and humidity sensor

// Arduino Mega 2560 Pins for OLED screen and DHT11 sensor
#define DHT11_PIN 7
#define sclk 41
#define mosi 37
#define cs 10
#define rst 8
#define dc 9

const int dry = 595;  // value for dry sensor
const int wet = 239;  // value for wet sensor

// Color definitions
#define BLACK 0x0000
#define WHITE 0xFFFF
#define RED 0xF800
#define GREEN 0x07E0
#define BLUE 0x001F

// Function to initialize the OLED display
Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, mosi, sclk, rst);

void setup(void) {
  Serial.begin(9600);
  Serial.print("hello!");
  display.begin();
  pinMode(4, OUTPUT);
  display.fillScreen(BLACK);
  display.setTextColor(RED);
  display.setCursor(0, 0);
  display.println("Soil Sensor:");
  display.setCursor(10, 25);
  display.println("Temp:");
  display.setCursor(10, 40);
  display.println("Humidity:");
}

void loop() {
  int chk = DHT.read11(DHT11_PIN);  // Temperature and humidity sensor reading
  delay(500);

  int sensorVal = analogRead(A1);
  int percentageHumidity = map(sensorVal, wet, dry, 100, 0);

  display.setTextColor(BLUE);
  display.setCursor(74, 0);
  display.print(percentageHumidity);
  display.println("%");
  display.setCursor(74, 25);

  int temp = (int)DHT.temperature;
  display.print(temp);
  display.println("C");

  display.setCursor(74, 40);
  display.print((int)DHT.humidity);
  display.println("%");
  
  // Conditions for Pump start and stop
  if ((percentageHumidity < 50) && (temp < 32)) {
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(4, LOW);
    delay(500);
  }

  // Clearing the Screen
  delay(200);
  display.fillRect(74, 0, 24, 20, BLACK);
  display.fillRect(74, 25, 24, 20, BLACK);
  display.fillRect(74, 40, 24, 20, BLACK);

}
