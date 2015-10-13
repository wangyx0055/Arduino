#include <IRremote.h>

IRsend irsend;

void setup()
{
  Serial.begin(9600);
}

void loop() {
      irsend.sendNEC(0x90A0060A, 32);
      delay(20);
      irsend.sendNEC(0x90A0060A, 32);
      delay(2000);
}
