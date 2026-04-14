#include <Esplora.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 11);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  int x = Esplora.readJoystickX();
  int y = Esplora.readJoystickY();

    if    (y < -50)  mySerial.print('F');
  else if (y > 50) mySerial.print('B');
  else if (x > 50)  mySerial.print('R');
  else if (x < -50) mySerial.print('L');

  if (Esplora.readButton(SWITCH_2) == LOW) mySerial.print('2');
  if (Esplora.readButton(SWITCH_1) == LOW) mySerial.print('1');
  if (Esplora.readButton(SWITCH_3) == LOW) mySerial.print('3');
  if (Esplora.readButton(SWITCH_4) == LOW) mySerial.print('4');

  delay(40);
}