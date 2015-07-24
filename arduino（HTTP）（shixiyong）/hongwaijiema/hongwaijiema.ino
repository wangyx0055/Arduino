#include <IRremote.h>
int RECV_PIN = 11;//定义红外接收器的引脚为11
IRsend irsend;    
IRrecv irrecv(RECV_PIN);
decode_results results;//解码结果放在decode_results构造的对象results里
void setup()
{
 Serial.begin(9600);
 irrecv.enableIRIn(); // 初始化红外接收器
}
void loop() {
    if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);//以16进制换行输出接收代码
    //results.value 是unsigned long型，头文件有介绍 
//    Serial.print(",  bits: ");
//    Serial.println(results.bits);
    irrecv.resume(); // 接收下一个值
  }
  delay(600);
}


