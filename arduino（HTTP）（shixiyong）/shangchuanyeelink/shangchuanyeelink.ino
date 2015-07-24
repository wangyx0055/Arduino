
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(12,OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:
 int sensorValue = random(1,20);//  Serial.println(sensorValue, DEC);
  digitalWrite(12,HIGH);
  Serial.println("POST /v1.0/device/19033/sensor/33334/datapoints HTTP/1.1"); //“/device/4290/sensor/9970/”device,sensor 后面的数值用你自己的替代
  Serial.println("Host: api.yeelink.net");
  Serial.print("Accept: *");
  Serial.print("/"); 
  Serial.println("*"); 
  Serial.print("U-ApiKey: "); 
  Serial.println("05736fff12f0e6d03de7a477e40ddbbd");   // 此处用你的APIKEY替代
  Serial.print("Content-Length: "); 
  int thisLength = 10 + getLength(sensorValue);
  Serial.println(thisLength);   
  Serial.println("Content-Type: application/x-www-form-urlencoded");
  Serial.println("Connection: close"); 
  Serial.println(); 
  Serial.print("{\"value\":");
  Serial.print(sensorValue);  
  Serial.println("}");
  delay(1000);
  digitalWrite(12,LOW);
  delay(9000);
}
int getLength(int someValue) {
  // there's at least one byte:
  int digits = 1;
  // continually divide the value by ten, 
  // adding one to the digit count for each
  // time you divide, until you're at 0:
  int dividend = someValue /10;
  while (dividend > 0) {
    dividend = dividend /10;
    digits++;
  }
  // return the number of digits:
  return digits;
}
