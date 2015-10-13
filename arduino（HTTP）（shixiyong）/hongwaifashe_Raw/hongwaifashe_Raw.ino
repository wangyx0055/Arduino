
#include <IRremote.h> 
  
IRsend irsend; 

unsigned long  buff1 = 3047689766 ;
void setup() 
{ 
    Serial.begin(9600);
} 
  
void loop() { 
//  irsend.kongTiao(2,38); 
  delay(30);

  irsend.sendSharp(buff1,32);
  delay(3000);
}
