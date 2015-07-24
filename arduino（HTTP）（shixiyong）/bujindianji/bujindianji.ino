#include <Stepper.h>
#define STEPS 100
Stepper myStepper(STEPS,8,9,10,11);
int stepCount = 0;
int Count = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  myStepper.setSpeed(90);
}
void loop() {
  // put your main code here, to run repeatedly:
 if(Serial.available() > 0)
   {
     stepCount = Serial.read(); 
      if (stepCount == '1')
      {
        myStepper.step(1000);
        Count=Count+1000;
	Serial.println(Count);  
      }    
      if (stepCount == '2')
      {
        myStepper.step(-1000);
        Count=Count-1000;
	Serial.println(Count);  
      }  
   }
}
