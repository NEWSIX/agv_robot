#include <Servo.h>
Servo myservo; 
int y = 1;
void setup()
{
myservo.attach(9);
}
void loop()
{
  if(y=1){
    myservo.write(0);
    Serial.println("A2");
    delay(1000);
  }  
  if(y=0){
    myservo.write(90); 
   Serial.println("A1");
    delay(1000); 
  }
}
