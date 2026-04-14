// Pin del LED (conecta el ánodo del LED + resistencia al pin, cátodo a GND)
const int ledPin = 2;

// Parámetros PWM (LEDC)
const int freq = 5000;       // Frecuencia PWM en Hz (5-5000Hz)
const int resolution = 8;    // Resolución en bits (8 bits -> 0..255 , 9 bits -> 0..511)

void setup() {

  // Inicia la comunicación serial para poder enviar valores desde el monitor serial
  Serial.begin(115200);

  // Asocia el pin al PWM configurando automáticamente frecuencia y resolución
  ledcAttach(ledPin, freq, resolution);

  Serial.println("Ingresa un valor de brillo entre 0 y 255:");
}

void loop() {

  // Si hay una línea completa disponible
  if (Serial.available()) {

    // Leer toda la línea enviada
    String input = Serial.readStringUntil('\n');

    // Elimina espacios y saltos de línea
    input.trim();

    // Convertir a entero
    int brillo = input.toInt();

    // Verifica que el valor esté dentro del rango válido
    if (brillo >= 0 && brillo <= 255) {

      // Cambia el duty cycle del PWM (brillo del LED)
      ledcWrite(ledPin, brillo);

      Serial.print("Brillo ajustado a: ");
      Serial.println(brillo);
    } 
    else {
      Serial.println("Valor invalido. Usa un numero entre 0 y 255.");
    }
  }
}