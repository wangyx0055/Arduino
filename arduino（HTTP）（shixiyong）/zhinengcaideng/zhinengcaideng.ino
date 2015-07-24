struct hash
{
  String key;
  String value;
};
unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 1000;
boolean ResponseBegin = false;
int led2Pwm = 127;
boolean isLeft = true;
boolean led2 = true;
String tempChar = "";
int keyIndex = 0, valueIndex = 0, index = 0, index1=0;
struct hash couple[2];
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(9,OUTPUT);
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
        valueIndex = 0 ; keyIndex = 0;  
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
}else if( couple[0].key == "\"controller\"")
{
  index = 1;
  index1 = 0;
}
    if(couple[index].key == "\"switch\"" ) 
    {
      if(couple[index].value == "1" && (led2) )
      {
      analogWrite(9, led2Pwm);
      led2 = false ;
       feedBack();      
      }
      else if(couple[index].value == "0"  )
      {
         analogWrite(9, 0);
         led2 = true;
         feedBack();
      }
      if(couple[index].value == "1"  ){        
        if(couple[index1].key == "\"controller\""){
          if(couple[index1].value == "0"  ){
            led2Pwm=127;
            analogWrite(10, led2Pwm);      
          }
          else if(couple[index1].value == "2" ){
            led2Pwm=255;
            analogWrite(10, led2Pwm);      
          }
               else if(couple[index1].value == "1"){
                    led2Pwm=10;
                    analogWrite(10, 10);          
               }          
        } 
      }      
      
      //reset all values
      couple[0].key = "";couple[0].value = "";
      couple[1].key = "";couple[1].value = "";     
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
  
