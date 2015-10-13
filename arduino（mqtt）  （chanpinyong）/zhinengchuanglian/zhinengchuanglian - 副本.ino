unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 30000;
boolean ResponseBegin = false;
String returnValue = "";
String a = ""; 
int kaiGuan , yaoKong;
char string[100];
char seps[]   = ":,";
char *token; 

void setup() {    //设置单片机初始状态
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(8,OUTPUT);
    pinMode(10,OUTPUT);
    digitalWrite(8, HIGH); 
    digitalWrite(10, HIGH); 
	getData();
}

void loop() {
   if(millis() - lastConnectionTime > postingInterval){   //wifi节点关闭后，重新开启节点
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
            switch(yaoKong ){                //根据指令发送相应的红外码，遥控电器
               case 1:
                digitalWrite(8, LOW);
                delay(1000); 
                digitalWrite(8, HIGH); 
                yaoKong = 0;
                break;
               case 2:
                digitalWrite(10, LOW);
                delay(1000); 
                digitalWrite(10, HIGH);
                yaoKong = 0;
                break;
               case 3:
                digitalWrite(8, LOW);
                digitalWrite(10, LOW);
                delay(1000); 
                digitalWrite(8, HIGH);
                digitalWrite(10,HIGH); 
                yaoKong = 0;
                break;
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

void getData(void) {     //设置wifi板节点，连接服务器
  Serial.println("dofile(\"mqtt.lua\")"); 
  lastConnectionTime = millis();
}

  
 
