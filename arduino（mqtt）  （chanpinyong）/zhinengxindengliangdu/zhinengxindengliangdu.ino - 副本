unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 30000; //重连时间
boolean ResponseBegin = false;
String returnValue = "";       
String a = "";
int kaiGuan , liangDu;
char string[100];
char seps[]   = ":,";
char *token;

void setup() {           //设置单片机初始状态
  // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(9,OUTPUT);  //彩灯必须接到单片机9脚
    getData();        
}
void loop() {       
   if(millis() - lastConnectionTime > postingInterval){  //wifi节点关闭后，重新开启节点
     getData();
   }
   
   if (Serial.available()) {  //读取并处理wifi板得到的服务器指令
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
   
   if (returnValue.length()!=0 && (ResponseBegin == false)){    //将指令转换格式
       for (int i = 0; i < returnValue.length()+1 ; i++){
         string[i] = returnValue[i];
       }      
    
       token = strtok( string, seps );      //将字符串分段处理
       while( token != NULL )        
       {
        a = token ;
        if(a == "{\"switch\"") {
        token = strtok( NULL, seps );
        a = token;
        kaiGuan = atoi(token);
       } 
        token = strtok( NULL, seps );
        a = token;    
        if (a == "\"controller\""){
            token = strtok( NULL, seps );
            a = token;
            liangDu = atoi(token);      
            if(kaiGuan ){         //根据指令改变灯的亮度
                analogWrite(9,liangDu);
            }
            else{
                digitalWrite(9,LOW);
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
void getData(void) {      //设置wifi板节点，连接服务器
    Serial.println("dofile(\"mqtt.lua\")"); 
    lastConnectionTime = millis();
}

  
