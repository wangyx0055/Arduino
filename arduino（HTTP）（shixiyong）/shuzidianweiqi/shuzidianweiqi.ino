 int cs = 11;
 int inc = 10;
 int ud = 9;
 
void setup() {
  // put your setup code here, to run once:
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(cs,OUTPUT);
  pinMode(inc,OUTPUT);  
  pinMode(ud,OUTPUT);  
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(4)  == LOW)
  {
    delay(2000);
     if(digitalRead(4)  == LOW)  
       {  
         zengjia();
       }
  }
   if(digitalRead(5)  == LOW)
  {
    delay(2000);
     if(digitalRead(5)  == LOW)  
       {  
         jianshao();
       }
  } 
}
void zengjia(){
  digitalWrite(cs,LOW);
  analogWrite(ud,155);
  analogWrite(inc,155);
  delay(500);
  digitalWrite(inc,LOW);
  delay(500);
  analogWrite(inc,155);
  analogWrite(cs,155);
  delay(500);
  digitalWrite(cs,LOW);
}
void jianshao(){
  digitalWrite(cs,LOW);
  digitalWrite(ud,LOW);
  analogWrite(inc,155);
  delay(500);
  digitalWrite(inc,LOW);
  delay(500);
  analogWrite(inc,155);
  analogWrite(cs,155);
  delay(500);
  digitalWrite(cs,LOW);  
}
  
