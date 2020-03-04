#include <Servo.h>
char key = '0' ;  
Servo servo_test;                 
int angle = 0; 
int Buzzer = 10;   

void setup() 
{
  Serial.begin(9600);
  servo_test.attach(9);
  pinMode(Buzzer, OUTPUT);
  
} 
void loop() 
{
  if (Serial.available() > 0) 
    {
     key = Serial.read();
      if (key == '0')
        {
         for(angle = 0; angle < 180; angle += 1)    // command to move from 0 degrees to 180 degrees 
          {                                  
            servo_test.write(angle);                 //command to rotate the servo to the specified angle
            delay(15);                       
          }          
            delay(1000);
            for(angle = 180; angle>=1; angle-=5)     // command to move from 180 degrees to 0 degrees 
          {                                
            servo_test.write(angle);              //command to rotate the servo to the specified angle
            delay(5);                       
          } 
            delay(1000);
        }
        
     }
   else if (key == '1')
    {
     for (int i = 0; i < 3; i++) 
     {
     digitalWrite(Buzzer,LOW);
     delay(100);
     digitalWrite(Buzzer,HIGH);
     delay(50);
     }
    }
   else if (key == '2') 
    {
     Serial.println("Hello All We love Arduino ");
    }
}
