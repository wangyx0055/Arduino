void setup() {
  // put your setup code here, to run once:
  pinMode(4,INPUT);
  pinMode(12,OUTPUT);
  digitalWrite(4,HIGH);   //先预设4管脚为高  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(4)  == LOW)
  {
    delay(2000);
     if(digitalRead(4)  == LOW)  
       {  
         digitalWrite(12,HIGH);
         Serial.println("OK");
         delay(1000);
         digitalWrite(12,LOW);
       }
  }
}
