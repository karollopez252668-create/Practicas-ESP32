// Librería para manejar teclados matriciales
#include <Keypad.h>

// Número de filas del teclado
const byte rowsCount = 4;

// Número de columnas del teclado
const byte columsCount = 3;

// Mapa de teclas del teclado (cómo están organizadas físicamente)
char keys[rowsCount][columsCount] = {
  { '1','2','3' },
  { '4','5','6' },
  { '7','8','9' },
  { 'D','0','S' }   // D = borrar, S = enviar / confirmar contraseña
};

// Pines del ESP32 conectados a las FILAS del teclado
byte rowPins[rowsCount] = { 13, 12, 14, 27 };

// Pines del ESP32 conectados a las COLUMNAS del teclado
byte columnPins[columsCount] = { 26, 25, 33 };

// Creación del objeto keypad usando:
// - el mapa de teclas
// - los pines de filas
// - los pines de columnas
// - número de filas y columnas
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);

// Pin donde está conectado el LED
const int ledPin = 32;

// Contraseña correcta
String password = "1234";

// Variable donde se almacenan las teclas que el usuario va presionando
String input = "";

void setup() {

  // Inicia comunicación serial para mostrar mensajes en el monitor serial
  Serial.begin(115200);

  // Configura el pin del LED como salida
  pinMode(ledPin, OUTPUT);

  // Asegura que el LED empiece apagado
  digitalWrite(ledPin, LOW);

  // Mensaje inicial
  Serial.println("Ingresa contraseña:");
}

void loop() {

  // Lee la tecla presionada (si no se presiona nada devuelve NULL)
  char key = keypad.getKey();

  // Si se presionó una tecla
  if (key) {

    // Muestra en el monitor serial la tecla presionada
    Serial.println(key);

    // Evalúa qué tecla fue presionada
    switch (key) {

      // Si se presiona 'S' se intenta validar la contraseña
      case 'S':

        // Compara lo que escribió el usuario con la contraseña guardada
        if (input == password) {

          Serial.println("Correcta!");

          // Enciende el LED durante 3 segundos
          digitalWrite(ledPin, HIGH);
          delay(3000);
          digitalWrite(ledPin, LOW);

        } else {

          Serial.println("Incorrecta!");

        }

        // Limpia el texto ingresado para intentar nuevamente
        input = "";

        Serial.println("Ingresa contraseña:");
        break;


      // Si se presiona 'D' se borra lo que se ha escrito
      case 'D':

        input = "";
        Serial.println("Borrado");
        break;


      // Cualquier otra tecla (número) se agrega al texto ingresado
      default:

        input += key;
        break;
    }
  }
}