
int dataBuff;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  pinMode(12,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available() > 0)
   {
     dataBuff = Serial.read();

     if (dataBuff == 'o')
      {
        digitalWrite(12,HIGH);
	Serial.println("Turn on");
      }  
     if (dataBuff == 'c')
      {
        digitalWrite(12,LOW);
	Serial.println("Turn off");
      }  
   }
}
