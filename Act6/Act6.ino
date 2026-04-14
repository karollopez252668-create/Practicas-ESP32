#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <DHT.h> // DHT sensor library

#define RST 15
#define CE 2
#define DC 4
#define DIN 23
#define CLK 18

#define DHTPIN 21
#define DHTTYPE DHT11

Adafruit_PCD8544 display = Adafruit_PCD8544(CLK, DIN, DC, CE, RST);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  display.begin();
  display.setContrast(40);
  dht.begin();

  display.clearDisplay();
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.setCursor(10, 16);
  display.println("Iniciando...");
  display.display();

  delay(2000);
}

void loop() {
  float temp = dht.readTemperature();
  float hum  = dht.readHumidity();

  display.clearDisplay();
  display.setTextSize(1);

  if (isnan(temp) || isnan(hum)) {
    display.setCursor(0, 0);
    display.println("Error DHT11");
  } else {
    Serial.print("Temperatura: "); Serial.print(temp, 1); Serial.println(" C");
    Serial.print("Humedad:     "); Serial.print(hum, 0);  Serial.println(" %");

    display.setCursor(0, 0);
    display.println("Temperatura:");
    display.setTextSize(2);
    display.setCursor(0, 10);
    display.print(temp, 1);
    display.println(" C");

    display.setTextSize(1);
    display.setCursor(0, 32);
    display.println("Humedad:");
    display.setCursor(50, 32);
    display.print(hum, 0);
    display.println("%");
  }
  display.display();
  delay(2000);
}