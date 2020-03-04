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
         for (int i = 0; i < 2; i++) 
          {
           digitalWrite(Buzzer,LOW);
           delay(100);
           digitalWrite(Buzzer,HIGH);
           delay(50);
          }  
         for(angle = 90; angle>=1; angle--)  
          {                                
           servo_test.write(angle);
           delay(5);                       
          } 
           delay(1000);
        }
    
       else if (key == '1') 
        {
          for (int i = 0; i < 2; i++) 
           {
            digitalWrite(Buzzer,LOW);
            delay(100);
            digitalWrite(Buzzer,HIGH);
            delay(50);
           }
          for(angle = 0; angle < 90; angle ++)   
           {                                
            servo_test.write(angle);
            delay(5);                       
           }
          delay(1000);
        }
     }
}
