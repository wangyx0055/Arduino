#include <IRremote.h>       //红外库
#include <avr/pgmspace.h>
   boolean ResponseBegin = false;
   String returnValue = "";// 串口接收数据
   String a = ""; 
   int kaiGuan , yaoKong,k;
   char string[100];
   char seps[]   = ":,";
   char *token;
   IRsend irsend;//定义红外发射引脚  ，必须接到uno板的3脚  
   const PROGMEM  unsigned int    butten0[37]={2950,3000,500,1450,550,1450,500,1500,500,1450,550,1450,500,1500,500,2450,500,1500,500,1500,500,1450,500,1500,500,1500,500,2450,500,1500,500,2450,500,2500,500,4000,500};
   const PROGMEM  unsigned int    butten1[37]={2900,3050,450,1500,450,1550,400,1600,400,1550,400,1600,450,1500,450,2550,450,1500,450,1550,450,1550,450,1500,450,1550,450,1550,450,1500,450,1550,400,2550,500,4000,450};  // 遥控器的键值，
   const PROGMEM  unsigned int    butten2[37]={2950,3000,450,1550,450,1500,450,1550,450,1550,450,1500,450,1500,500,2500,450,1550,450,1550,450,1500,450,1500,500,1500,450,1550,450,1550,450,2500,450,1550,450,4000,450};
   const PROGMEM  unsigned int    butten3[37]={2950,2950,500,1500,500,1500,450,1500,450,1550,450,1500,500,1500,450,2500,500,1500,450,1550,450,1500,500,1500,500,1500,450,1500,500,1500,450,2500,450,2550,500,3950,500};
   const PROGMEM  unsigned int    butten4[37]={2900,3050,450,1500,500,1500,450,1500,500,1500,500,1500,450,1500,500,2500,450,1500,500,1500,500,1500,450,1500,500,1500,500,1500,450,2500,500,1500,450,1500,500,4000,500};
   const PROGMEM  unsigned int    butten5[37]={2900,3000,450,1550,450,1550,450,1500,500,1500,500,1450,500,1500,500,2500,450,1500,500,1500,450,1500,500,1500,500,1500,450,1500,450,2550,450,1500,500,2500,450,4050,450};
   const PROGMEM  unsigned int    butten6[37]={2950,3000,450,1550,400,1550,450,1550,450,1500,500,1500,450,1550,450,2500,450,1550,450,1500,500,1500,450,1550,450,1500,500,1500,450,2500,500,2500,450,1500,500,4000,500};
   const PROGMEM  unsigned int    butten7[37]={2900,3050,400,1550,450,1550,450,1500,450,1550,450,1550,450,1500,450,2550,450,1500,450,1550,450,1550,450,1500,450,1550,450,1550,400,2550,450,2500,450,2550,450,4050,400};
   const PROGMEM  unsigned int    butten8[37]={2950,2950,500,1500,500,1500,450,1500,500,1500,500,1500,450,1500,500,2450,500,1500,500,1500,500,1500,450,1500,500,1500,450,2500,500,1500,450,1500,500,1500,500,4000,450};
   const PROGMEM  unsigned int    butten9[37]={2900,3000,500,1500,450,1500,500,1500,500,1500,450,1500,500,1500,500,2450,500,1500,500,1500,450,1500,500,1500,450,1500,500,2500,500,1500,450,1500,500,2500,500,3950,500};
   const PROGMEM  unsigned int    butten10[37]={2950,3000,500,1450,550,1450,500,1500,500,1450,550,1450,500,1500,500,2450,500,1500,500,1500,500,1450,500,1500,500,1500,500,2450,500,1500,500,2450,500,2500,500,4000,500};
   const PROGMEM  unsigned int    butten11[37]={2900,3050,450,1500,450,1550,450,1550,400,1550,450,1550,450,1500,450,2550,450,1550,400,1550,450,1550,450,1500,450,2550,450,1500,450,2550,450,1550,400,2550,450,4050,450};
   const PROGMEM  unsigned int    butten12[37]={2900,3000,450,1550,450,1500,450,1550,450,1550,450,1500,450,1550,450,2500,450,1550,450,1550,450,1500,500,1500,450,2500,450,1550,500,1500,450,1500,500,2500,500,3950,500};
   const PROGMEM  unsigned int    butten13[37]={2900,3000,500,1500,450,1500,500,1500,500,1500,450,1500,500,1500,500,2450,500,1500,500,1500,450,1500,500,1500,500,2450,500,1500,500,1500,450,1500,500,1500,500,4000,450};
   const PROGMEM  unsigned int    butten14[37]={2900,3050,450,1500,450,1550,450,1550,450,1500,450,1550,450,1500,500,2500,450,1550,450,1500,450,1550,450,1500,450,2550,450,1550,400,1550,450,2550,450,2500,500,4000,450};
   const PROGMEM  unsigned int    butten15[37]={2950,3000,450,1500,500,1500,500,1500,450,1500,500,1500,500,1500,450,2500,500,1500,450,1500,500,1500,500,1500,450,2500,500,1500,450,1500,500,2500,450,1500,550,3950,500};
   const unsigned int* const butten[16] = {butten0,butten1,butten2,butten3,butten4,butten5,butten6,butten7,butten8,butten9,butten10,butten11,butten12,butten13,butten14,butten15};

   unsigned long lastConnectionTime = 0;
   const unsigned long postingInterval = 30000;//每次连接时间
   unsigned int hongWai[37];
   unsigned int displayInt;
   
void setup() {
  // put your setup code here,
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
                for (k = 0; k < 37; k++)
                {
                    hongWai[k] = pgm_read_word_near(butten[yaoKong] + k);         
                }
                irsend.sendRaw(hongWai,37,38);
                for (k = 0; k < 37; k++)
                {
                    hongWai[k] = 0;
                }                
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

  
