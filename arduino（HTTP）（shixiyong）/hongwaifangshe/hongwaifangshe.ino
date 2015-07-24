#include <IRremote.h>

IRsend irsend;

void setup()
{
  Serial.begin(9600);
}

void loop() {
//  if (Serial.read() != -1) {
//    for (int i = 0; i < 3; i++) {
//      irsend.sendSony(0xA90, 12); // Sony TV power code
//      delay(2000);
//      irsend.sendNEC(0x4CB3817E, 32);
//      delay(2000);
      irsend.sendNEC(0x5A0419DC, 32);
      delay(2000);
//    }
//  }
}
