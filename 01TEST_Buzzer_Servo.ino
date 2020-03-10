#include <Servo.h>
char key = '0' ;  
Servo servo_test;                 
int angle = 0; 
int Buzzer = 4;
int LED = 3;

const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;
   

void setup() 
{
  Serial.begin(9600);
  servo_test.attach(2);
  pinMode(Buzzer, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
 
} 

void loop() 
{
 Ultrasonic();
 Mode();
 
}

void Ultrasonic()
{
 digitalWrite(trigPin, HIGH);
 delay(1);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = (duration/2) / 29.1;
 Serial.println(distance);
 if (distance <= 10)
 { 
  for (int i = 0; i < 2; i++) 
   {
    digitalWrite(Buzzer,LOW);
    digitalWrite(LED,HIGH);
    delay(50);
    digitalWrite(Buzzer,HIGH);
    digitalWrite(LED,LOW);
    delay(50);
   }  
 }
}

void Mode()
{
  if (Serial.available() > 0)
    {
      key = Serial.read(); 
      if (key == '0')
        { 
         Servo_0();
         BuzzLED();
        }
       else if (key == '1') 
        {
         Servo_1();
         BuzzLED();
        }
     }
}

void BuzzLED()
{ 
  digitalWrite(Buzzer, HIGH);
  for (int i = 0; i < 2; i++) 
   {
    digitalWrite(Buzzer,LOW);
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(Buzzer,HIGH);
    digitalWrite(LED,LOW);
    delay(50);
   }
  delay(1000);
}

void Servo_0()
{
  for(angle = 90; angle>=1; angle--)  
          {                                
           servo_test.write(angle);
           delay(5);                       
          } 
}
void Servo_1()
{
  for(angle = 0; angle < 90; angle ++)   
          {                                
           servo_test.write(angle);
           delay(5);                       
          } 
}
