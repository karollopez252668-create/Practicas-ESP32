#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// PINES
#define RST 15
#define CE 2
#define DC 4
#define DIN 16 //en el esp32 es RX2
#define CLK 17 //en el esp32 es TX2

Adafruit_PCD8544 display = Adafruit_PCD8544(CLK, DIN, DC, CE, RST);

void setup() {
  display.begin();
  display.setContrast(50);

  display.clearDisplay();
  
  display.setTextSize(2);

  //BLACK para ESCRIBIR / WHITE para BORRAR
  display.setTextColor(BLACK);

  display.setCursor(0,0); //X, Y , tamaño de pantalla x = 84,y = 48
  display.println("HOLA");

  display.setCursor(24, 24);
  display.println("MUNDO");

  display.display();
}

void loop() {
}