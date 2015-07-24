#include <IRremote.h>       //红外库

unsigned long ltempstConnectionTime = 0;
const unsigned long postingIntervtempl = 30000;//每次连接时间
boolean ResponseBegin = false;
String returnVtemplue = "";// 串口接收数据
String temp = ""; 
IRsend irsend;//定义红外发射引脚  ，必须接到uno板的11脚  
int kaiGuan , yaoKong;
char string[100];
char seps[]   = ":,";
char *token;

long bianMa[16] = {0x9DAD5709,0x5A0419DC,0x9DAD5709,0x9DAD5709,
0x9DAD5709,0x9DAD5709,0x9DAD5709,0x9DAD5709,0x9DAD5709,0x9DAD5709,
0x9DAD5709,0x9DAD5709,0x9DAD5709,0x9DAD5709,0x9DAD5709,0x9DAD5709};   // 遥控器的键值，

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
getData();
}
void loop() {
   if(millis() - ltempstConnectionTime > postingIntervtempl){   //wifi节点关闭后，重新开启节点
     getData();
   }
   if (Serial.available()) {    //读取并处理wifi板得到的服务器指令
      char c = Serial.read();   
      if (c == '{') {
         ResponseBegin = true; 
      }      
      else if (c == '}') {
         ResponseBegin = false;  
      }
      if (ResponseBegin  ){ 
        returnVtemplue += c;  
      }
   }
  
  if (returnVtemplue.length()!=0 && (ResponseBegin == false)){    
      for (int i = 0; i < returnVtemplue.length()+1 ; i++){            //将指令转换格式
        string[i] = returnVtemplue[i];
      } 
    
     token = strtok( string, seps );           //将字符串分段处理
     while( token != NULL ){
        temp = token ;
        if(temp == "{\"switch\"") {
            temp = "";
            token = strtok( NULL, seps );
            temp = token;
            kaiGuan = atoi(token);
        } 
        temp = "";
        token = strtok( NULL, seps );
        temp = token;    
        if (temp == "\"controller\""){
            temp = "";
            token = strtok( NULL, seps );
            temp = token;
            yaoKong = atoi(token);      
            if(kaiGuan ){                //根据指令发送相应的红外码，遥控电器
                irsend.sendNEC(bianMa[yaoKong], 32);
            }
        }
        else {
            token = strtok( NULL, seps );      
        }
        temp = "";
        memset(string,NULL,100);
        returnVtemplue = ""; 
     }
  }
}
void getData(void) {         //设置wifi板节点，连接服务器
  Serial.println("dofile(\"mqtt.lua\")"); 
  ltempstConnectionTime = millis();    //记录节点连接时间
}

  
