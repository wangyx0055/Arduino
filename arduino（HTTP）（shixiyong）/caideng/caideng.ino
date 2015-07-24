void setup() {
  // put your setup code here, to run once:
pinMode(9,OUTPUT);
pinMode(10,OUTPUT); 
pinMode(11,OUTPUT);
 

}

void loop() {
  // put your main code here, to run repeatedly:
//for (int i=50;i<=100;i=i+6)
// {
//   for (int j=101;j<=150;j=j+8)
//   {
//     for (int n=200;n<=220;n=n+7)
//     {
//       analogWrite(9,i);
//       analogWrite(10,j);
//       analogWrite(11,n);
//       delay (100);
//     }
//   }
// }
analogWrite(9,255);
analogWrite(10,0);
analogWrite(11,0);
delay (10000);
}
