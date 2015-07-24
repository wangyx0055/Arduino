/*
 The circuit:
  * All A pins  of AD5206 connected to +5V
  * All B pins of AD5206 connected to ground
  * An LED and a 220-ohm resisor in series connected from each W pin to ground
  * CS - to digital pin 10  (SS pin)
  * SDI - to digital pin 11 (MOSI pin)
  * CLK - to digital pin 13 (SCK pin)
*/


// inslude the SPI library:
#include <SPI.h>


// set pin 10 as the slave select for the digital pot:
const int slaveSelectPin = 10;
  int i = 0;
  int j = 0;

void setup() {
  // set the slaveSelectPin as an output:
  pinMode (slaveSelectPin, OUTPUT);
  // initialize SPI:
  SPI.begin();
  pinMode(4,INPUT);
  digitalWrite(4,HIGH);
  pinMode(5,OUTPUT);
}

void loop() {
  if(digitalRead(4)  == LOW)
  {
    delay(2000);
     if(digitalRead(4)  == LOW && j < 255)  
       {  
        digitalWrite(5,HIGH);
         j = 200 ;
        digitalPotWrite(i, j);  
       }
  }
  digitalWrite(5,LOW);
 }


void digitalPotWrite(int address, int value) {
  // take the SS pin low to select the chip:
  digitalWrite(slaveSelectPin, LOW);
  //  send in the address and value via SPI:
  SPI.transfer(address);
  SPI.transfer(value);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);
}
