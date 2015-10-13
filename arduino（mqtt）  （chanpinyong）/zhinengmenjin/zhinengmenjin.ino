unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 30000;
boolean ResponseBegin = false;
String returnValue = ""; 

void setup() {  //设置单片机初始状态
  // put your setup code here, to run once:
    Serial.begin(9600);  //设置串口波特率
    pinMode(3,OUTPUT);   //门禁必须接到单片机9脚
    getData();
}
void loop() {
   if(millis() - lastConnectionTime > postingInterval){    //wifi节点关闭后，重新开启节点
     getData();
   }
   if (Serial.available()) {   //读取并处理wifi板得到的服务器指令
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
   if (returnValue.length()!=0 && (ResponseBegin == false)){  //根据相应的指令完成门禁的开关
      if (returnValue.charAt(returnValue.length() - 1) == '1' && (digitalRead(3) == LOW) ){ 
         digitalWrite(3, HIGH);        
      }
      else if(returnValue.charAt(returnValue.length() - 1 ) == '0' ) {
         digitalWrite(3, LOW);      
      }  
      returnValue = ""; 
   }
}
void getData(void) {  //设置wifi板节点，连接服务器
  Serial.println("dofile(\"mqtt.lua\")"); 
  lastConnectionTime = millis();
}

  
