int potPin = 0 ;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);//设置波特率
}

void loop() {
  // put your main code here, to run repeatedly:
int val;//定义变量
int dat;//定义变量
val=analogRead(0);// 读取传感器的模拟值并赋值给val
dat=(125*val)>>8;//温度计算公式
Serial.print("Tep:");//原样输出显示Tep 字符串代表温度
Serial.print(dat);//输出显示dat 的值
Serial.println("C");//原样输出显示C 字符串
delay(500);//延时0.5 秒

}
