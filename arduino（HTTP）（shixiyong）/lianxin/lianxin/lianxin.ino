#include <IRremote.h>       //红外库

unsigned long ltempstConnectionTime = 0;
const unsigned long postingIntervtempl = 30000;//每次连接时间
boolean ResponseBegin = false;
String temp = ""; 
IRsend irsend;//定义红外发射引脚
int kaiGuan , yaoKong;
char string[100]; //
 int jiShu = 0;
char seps[]   = ":,";
char *token;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(12,OUTPUT);
pinMode(9,OUTPUT);
getData();
}
void loop() {
   if(millis() - ltempstConnectionTime > postingIntervtempl){ 
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
      string[jiShu] = c;  
      jiShu = jiShu+1;
    }
   }
   if (jiShu && (ResponseBegin == false)){
//      for (int i = 0; i < returnVtemplue.length()+1 ; i++)
//     {
//      string[i] = returnVtemplue[i];
//     } 
    
     token = strtok( string, seps );
     while( token != NULL )
   {
      temp = token ;
    if(temp == "{\"switch\"") {
      temp = "";
      token = strtok( NULL, seps );
      temp = token;
      kaiGuan = atoi(token);
    } 
      temp = "";
      token = strtok( NULL, seps );
      temp = token;    
     if (temp == "\"controller\""){
      temp = "";
      token = strtok( NULL, seps );
      temp = token;
      yaoKong = atoi(token);      
      if(kaiGuan ){
        switch (yaoKong){       
          case 1:
            irsend.sendNEC(0x9DAD5709, 32);
            digitalWrite (9,HIGH);
            break;
          case 2:
            irsend.sendNEC(0x5A0419DC, 32);
            digitalWrite (9,LOW);
            break;
          case 3:
            irsend.sendNEC(0x9DAD5709, 32);
            break;
          case 4:
            irsend.sendNEC(0x5A0419DC, 32);
            break;
          case 5:
            irsend.sendNEC(0x9DAD5709, 32);
            break;
          case 6:
            irsend.sendNEC(0x5A0419DC, 32);
          break; 
         } 
      }
      else{
        digitalWrite(9,LOW);
      }
    }
    else {
      token = strtok( NULL, seps );      
    }
    temp = "";
   memset(string,NULL,100); 
   }
  }
}
void getData(void) {
  Serial.println("dofile(\"mqtt.lua\")"); 
  ltempstConnectionTime = millis();
}

  
