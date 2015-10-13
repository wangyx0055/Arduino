#include <IRremote.h>       //红外库

unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 30000;//每次连接时间
boolean ResponseBegin = false;
String returnValue = "";// 串口接收数据
String a = ""; 
IRsend irsend;//定义红外发射引脚  ，必须接到uno板的11脚  
int kaiGuan , yaoKong;
char string[100];
char seps[]   = ":,";
char *token;

long bianMa[16] = {0x9DAD5709,0xC1AA09F6,0xC1AA59A6,0xC1AA619E,
0xC1AAE11E,0xC1AA11EE,0xC1AA916E,0x5D8011C8,0x71D06673,0xFD213B16,
0x4B3D41B9,0x65A52F28,0x5105CA72,0xC5B4F5CF,0x76EC43A2,0x69CE021D};   // 遥控器的键值，

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
getData();
}
void loop() {
   if(millis() - lastConnectionTime > postingInterval){   //wifi节点关闭后，重新开启节点
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
      for (int i = 0; i < returnValue.length()+1 ; i++){            //将指令转换格式
        string[i] = returnValue[i];
      } 
    
     token = strtok( string, seps );           //将字符串分段处理
     while( token != NULL ){
        a = token ;
        if(a == "{\"switch\"") {
            a = "";
            token = strtok( NULL, seps );
            a = token;
            kaiGuan = atoi(token);
        } 
        a = "";
        token = strtok( NULL, seps );
        a = token;    
        if (a == "\"controller\""){
            a = "";
            token = strtok( NULL, seps );
            a = token;
            yaoKong = atoi(token);      
            if(kaiGuan ){                //根据指令发送相应的红外码，遥控电器
                irsend.sendNEC(bianMa[yaoKong], 32);
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
void getData(void) {         //设置wifi板节点，连接服务器
  Serial.println("dofile(\"mqtt.lua\")"); 
  lastConnectionTime = millis();    //记录节点连接时间
}

  
