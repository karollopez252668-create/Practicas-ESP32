#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <math.h>

// Pines de la pantalla Nokia 5110
#define PIN_RST  15
#define PIN_CE    2
#define PIN_DC    4
#define PIN_DIN  23
#define PIN_CLK  18

// Pin de recepción Serial2 (datos del Esplora)
#define PIN_RX2  16

// Dimensiones de la pantalla
#define SCREEN_W  84
#define SCREEN_H  48
#define SCREEN_CY 24   // centro vertical

// Config del jugador
#define MOVE_SPEED  0.15f
#define ROT_SPEED   0.10f
#define FOV         1.00f   // campo de visión en radianes

// Mapa del mundo en (8x8)
// '#' = pared   '.' = espacio libre
#define MAP_W 8
#define MAP_H 8

const char worldMap[MAP_H][MAP_W + 1] = {
  "########",
  "#......#",
  "#..#...#",
  "#......#",
  "#..#...#",
  "#......#",
  "#......#",
  "########"
};

// Úbicación del jugador
float playerX = 1.5f;
float playerY = 1.5f;
float playerA = 0.0f;   // ángulo de visión en radianes

// Pantalla
Adafruit_PCD8544 display = Adafruit_PCD8544(PIN_CLK, PIN_DIN, PIN_DC, PIN_CE, PIN_RST);

// Devuelve true si la posición (x, y) es pared
bool isWall(float x, float y) {
  int col = (int)x;
  int row = (int)y;

  if (col < 0 || col >= MAP_W) return true;
  if (row < 0 || row >= MAP_H) return true;

  return worldMap[row][col] == '#';
}

// Comandos que manda el arduino esplora
void handleCommand(char cmd) {
  float newX = playerX;
  float newY = playerY;

  switch (cmd) {
    case 'F':   // avanzar (Foward)
      newX += cos(playerA) * MOVE_SPEED;
      newY += sin(playerA) * MOVE_SPEED;
      break;

    case 'B':   // retroceder (Back)
      newX -= cos(playerA) * MOVE_SPEED;
      newY -= sin(playerA) * MOVE_SPEED;
      break;

    case 'L':   // girar izquierda (Left)
      playerA -= ROT_SPEED;
      break;

    case 'R':   // girar derecha (Right)
      playerA += ROT_SPEED;
      break;

    case '1':   // botón 1  / switch 1
      break;

    case '2':   // botón 2 / switch 2
      break;

    case '3':   // botón 3 / switch 3
      break;

    case '4':   // botón 4 / switch 4
      break;
  }

  // si no está pegado a la pared se puede mover
  if (!isWall(newX, newY)) {
    playerX = newX;
    playerY = newY;
  }
}

// FOV DEL JUGADOR en forma de CONO
void castRay(int screenX) {
  float rayAngle = (playerA - FOV / 2.0f)
                 + ((float)screenX / SCREEN_W) * FOV;
  float dist = 0.05f;
  while (dist < 16.0f && !isWall(playerX + cos(rayAngle) * dist,
                                  playerY + sin(rayAngle) * dist)) {
    dist += 0.05f;
  }

  float correctedDist = dist * cos(rayAngle - playerA);
  int wallHeight = constrain((int)(SCREEN_H / correctedDist), 0, SCREEN_H);

  int top    = SCREEN_CY - wallHeight / 2;
  int bottom = SCREEN_CY + wallHeight / 2;

  display.drawLine(screenX, top, screenX, bottom, BLACK);
}

// mira en el centro
void drawCrosshair() {
  display.drawLine(38, SCREEN_CY, 46, SCREEN_CY, BLACK);
  display.drawLine(42, 20, 42, 28, BLACK);
  display.drawPixel(42, SCREEN_CY, WHITE);
}

void render() {
  display.clearDisplay();
  // pone un rayo por cada columna de pantalla
  for (int x = 0; x < SCREEN_W; x++) {
    castRay(x);
  }
  drawCrosshair();
  display.display();
}

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, PIN_RX2, 17);

  display.begin();
  display.setContrast(55);
  display.clearDisplay();
  display.display();
}

void loop() {
  // recibe los comandos del esplora
  while (Serial2.available()) {
    char cmd = Serial2.read();
    Serial.print("Recibido: ");
    Serial.println(cmd);
    handleCommand(cmd);
  }

  render();
}