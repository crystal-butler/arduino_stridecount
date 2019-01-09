#include <EEPROM.h>

int a = 0;
int value;

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 1024; i++) {
    EEPROM.write (i, 0);
  }
}

void loop() {
  value = EEPROM.read(a);

  Serial.print(a);
  Serial.print("\t");
  Serial.print(value);
  Serial.println();

  a = a + 1;

  if (a == 1024)
    a = 0;

  delay(500);
}
