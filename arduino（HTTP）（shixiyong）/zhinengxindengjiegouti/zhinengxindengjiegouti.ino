struct hash
{
  String key;
  String value;
};
unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 3000;
boolean ResponseBegin = false;

boolean isLeft = true;
String tempChar = "";
int keyIndex = 0, valueIndex = 0, index = 0 , index1 = 0;
struct hash couple[2];
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(12,OUTPUT);
}
void loop() 
{
   if(millis() - lastConnectionTime > postingInterval){ 
     getData();
   }
   if (Serial.available()) {  
      char c = Serial.read();   
      if (c == '{') {
         ResponseBegin = true; 
      }else if (c == '}'){
        couple[valueIndex].value = tempChar;
        isLeft = true;
        tempChar = "";
        ResponseBegin = false;  
      }
     if (ResponseBegin  && c != '{'){  
        if(c == ':' || c == ','){
           if(isLeft){
            couple[keyIndex].key = tempChar;
            isLeft = false;
            keyIndex++;
          }else{
            couple[valueIndex].value = tempChar;
            isLeft = true;
            valueIndex++;
          }
          if( tempChar != ""){
            tempChar = "";
          }
        }else{
          tempChar += c;
        }
     }
   }
// couple[0] or couple[1]   
if( couple[0].key == "\"switch\"")
{
  index = 0;
  index1 = 1;
}else if( couple[1].key == "\"switch\"")
{
  index = 1;
  index1 = 0;
}
    if(couple[index].key == "\"switch\"") 
    {
      if(couple[index].value == "1" && (digitalRead(12) == LOW) )
      {
        digitalWrite(12,HIGH);
        feedBack();
      }
      else if(couple[index].value == "0" && (digitalRead(12) == HIGH) )
      {
         digitalWrite(12, LOW);
         feedBack();
      }
      //reset all values
      couple[index].key = "";couple[index].value = "";
      couple[index1].key = "";couple[index1].value = "";
      keyIndex = 0; valueIndex = 0;
    }
   
}
void getData(void) 
{
  Serial.println("GET /index.php/devices/7/value HTTP/1.1");
  Serial.println("Host: 192.168.1.1");
  Serial.print("Accept: *");
  Serial.print("/"); 
  Serial.println("*"); 
  Serial.println("Content-Length: 0"); 
  Serial.println("Connection: close");
  Serial.println(); 
  Serial.println(); 
  lastConnectionTime = millis();
}
void feedBack(void)  
{
  Serial.println("POST /index.php/feedback/led1 HTTP/1.1");
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
  
