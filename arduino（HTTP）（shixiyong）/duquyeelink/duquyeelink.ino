unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 3*1000;
boolean ResponseBegin = false;
String returnValue = ""; 
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(12,OUTPUT);
pinMode(10,OUTPUT);
pinMode(8,OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
// int sensorValue = random(1,20);//  Serial.println(sensorValue, DEC);

   if(millis() - lastConnectionTime > postingInterval) 
    getData();

  if (Serial.available()) {  
   char c = Serial.read();   
   if (c == '{') {
   ResponseBegin = true; 
   digitalWrite(10, HIGH);
   digitalWrite(8, LOW); 
   }
   else if (c == '}') {
    ResponseBegin = false;  
    digitalWrite(10, LOW); 
    digitalWrite(8, HIGH); 
   }
   if (ResponseBegin){ 
   returnValue += c;  
   }
  }

   if (returnValue.length()!=0 && (ResponseBegin == false)){
      if (returnValue.charAt(returnValue.length() - 1) == '1') 
         digitalWrite(12, HIGH);  
      else if(returnValue.charAt(returnValue.length() - 1 ) == '0') 
         digitalWrite(12, LOW);  
      returnValue = ""; 
   }

}
void getData(void) {
  Serial.println("GET /v1.0/device/19033/sensor/33170/datapoints HTTP/1.1"); //“/device/4290/sensor/9970/”device,sensor 后面的数值用你自己的替代
  Serial.println("Host: api.yeelink.net");
  Serial.print("Accept: *");
  Serial.print("/"); 
  Serial.println("*"); 
  Serial.print("U-ApiKey: "); 
  Serial.println("05736fff12f0e6d03de7a477e40ddbbd");   // 此处用你的APIKEY替代
  Serial.println("Content-Length: 0"); 
  Serial.println("Connection: close");
  Serial.println(); 
  Serial.println(); 
  lastConnectionTime = millis();
}
  
