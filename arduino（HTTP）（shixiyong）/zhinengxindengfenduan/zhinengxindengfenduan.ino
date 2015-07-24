unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 1000;
boolean ResponseBegin = false;
String returnValue = ""; 
String a = "";
char string[100];
char seps[]   = ":,";
char *token;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(12,OUTPUT);
pinMode(9,OUTPUT);
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
      if(a == "1" && (digitalRead(12) == LOW) ){
        digitalWrite(12,HIGH);
        feedBack();
      }
      else if(a == "0" && (digitalRead(12) == HIGH) ){
         digitalWrite(12, LOW);
         feedBack();
      }
    } 
      a = "";
      token = strtok( NULL, seps );
      a = token;    
     if (a == "\"controller\""){
      a = "";
      token = strtok( NULL, seps );
      a = token;
      if(a == "1" && (digitalRead(9) == LOW) ){
        digitalWrite(9,HIGH);
        feedBack();
      }
      else if(a == "0" && (digitalRead(9) == HIGH) ){
         digitalWrite(9, LOW);
         feedBack();
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
  Serial.println("GET /index.php/devices/7/value HTTP/1.1"); //“/device/4290/sensor/9970/”device,sensor 后面的数值用你自己的替代
  Serial.println("Host: 192.168.1.1");
  Serial.print("Accept: *");
  Serial.print("/"); 
  Serial.println("*"); 
 // Serial.print("U-ApiKey: "); 
//  Serial.println("05736fff12f0e6d03de7a477e40ddbbd");   // 此处用你的APIKEY替代
  Serial.println("Content-Length: 0"); 
  Serial.println("Connection: close");
  Serial.println(); 
  Serial.println(); 
  lastConnectionTime = millis();
}
void feedBack(void)  {
  Serial.println("POST /index.php/feedback/led1 HTTP/1.1"); //“/device/4290/sensor/9970/”device,sensor 后面的数值用你自己的替代
  Serial.println("Host: 192.168.1.1");
  Serial.print("Accept: *");
  Serial.print("/"); 
  Serial.println("*"); 
  Serial.print("Content-Length:10 ");   
  Serial.println("Content-Type: application/x-www-form-urlencoded");
  Serial.println("Connection: close"); 
  Serial.println(); 
  Serial.print("{\"code\":0}"); 
  }
  
