#include <SPI.h>

unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 30000;
boolean ResponseBegin = false;
String returnValue = ""; 
String a = "";
int kaiGuan , liangDu ,dianZu;
char string[100];
char seps[]   = ":,";
char *token;
const int slaveSelectPin = 10;
double yingShe1, yingShe2 ;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(9,OUTPUT);
getData();
pinMode (slaveSelectPin, OUTPUT);
SPI.begin();
}
void loop() {
   if(millis() - lastConnectionTime > postingInterval){ 
     getData();
   }
   if (Serial.available()) {  
      char c = Serial.read();   
      if (c == '{') {
         ResponseBegin = true; 
      }      
      else if (c == '}') {
         ResponseBegin = false;  
      }
   if (ResponseBegin  ){ 
      returnValue += c;  
    }
   }
   if (returnValue.length()!=0 && (ResponseBegin == false)){
      for (int i = 0; i < returnValue.length()+1 ; i++)
     {
      string[i] = returnValue[i];
     }      
    
     token = strtok( string, seps );
     while( token != NULL )
   {
      a = token ;
    if(a == "{\"switch\"") {
      a = "";
      token = strtok( NULL, seps );
      a = token;
      kaiGuan = atoi(token);
    } 
      a = "";
      token = strtok( NULL, seps );
      a = token;    
     if (a == "\"controller\""){
      a = "";
      token = strtok( NULL, seps );
      a = token;
      liangDu = atoi(token);      
      if(kaiGuan ){
         analogWrite(9,liangDu);
         yingShe1 = (double) liangDu / 2.5;
         yingShe2 = pow(yingShe1 , 1.5);
         dianZu = (int)yingShe2 ;
         digitalPotWrite(1  , dianZu);
         dianZu = 0 ;
      }
      else{
        digitalWrite(9,LOW);
      }
    }
    else {
      token = strtok( NULL, seps );      
    }
    a = "";
   memset(string,NULL,100);
   returnValue = ""; 
   }
  }
}
void getData(void) {
  Serial.println("dofile(\"mqtt.lua\")"); 
  lastConnectionTime = millis();
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

  
