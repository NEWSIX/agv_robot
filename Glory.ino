#include<AFMotor.h>
#include <Servo.h>

AF_DCMotor motor1(3);
AF_DCMotor motor2(4);

Servo servo_test;
/*------------------------PIN------------------------*/
const int Buzzer = 31;
const int trigPin = 36;
const int echoPin = 38;
const int Object_Sensor = 33;
const int s0 = 51;  
const int s1 = 49;  
const int s2 = 45;  
const int s3 = 47;  
const int out = 43;  
const int sensorPin0 = 52;
const int sensorPin1 = 48;
const int sensorPin2 = 46;
const int sensorPin3 = 44;
const int sensorPin4 = 42;
const int sensorPin5 = 40;
const int sensorPin6 = 22;
/*---------------------------------------------------*/
int red = 0 , green = 0 , blue = 0 , yellow = 0; 
int sensorValue0 = 0 ,sensorValue1=0 ,sensorValue2=0 ,sensorValue3=0 ,sensorValue4=0 ,sensorValue5=0 ,sensorValue6=0;
long duration;
int distance;
int spd1 = 0 , spd2 = 0;

String Located ,RGB;
String OBJECT_VAL , RGB_VAL;

void setup() 
{   
    Serial.begin(9600);
    servo_test.attach(10);
    pinMode(Buzzer, OUTPUT);
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT);
    pinMode(s0, OUTPUT);  
    pinMode(s1, OUTPUT);  
    pinMode(s2, OUTPUT);  
    pinMode(s3, OUTPUT);  
    pinMode(out, INPUT);  
    digitalWrite(s0, HIGH);  
    digitalWrite(s1, HIGH); 
    pinMode(INPUT, sensorPin0);
    pinMode(INPUT, sensorPin1);
    pinMode(INPUT, sensorPin2);
    pinMode(INPUT, sensorPin3);
    pinMode(INPUT, sensorPin4);
    pinMode(INPUT, sensorPin5);
    pinMode(INPUT, sensorPin6);
    pinMode(INPUT, Object_Sensor);
}

void loop() 
{
    object();
    inputDIGITAL();
    Ultrasonic();

}

/*------------------------OBJECT SENSOR------------------------*/
void object()
{
    int OBJECT=digitalRead(Object_Sensor);
    if (OBJECT == 0)
    {
        RGB_color();
        RGB_compare();
        stations();
    }
    else 
        George();
}

/*------------------------RGB------------------------*/
void RGB_color()  
{
    digitalWrite(s2, LOW);  
    digitalWrite(s3, LOW);  
    red = pulseIn(out, digitalRead(out) == LOW ? LOW : HIGH);  
    digitalWrite(s3, HIGH);  
    blue = pulseIn(out, digitalRead(out) == LOW ? HIGH : HIGH);  
    digitalWrite(s2, HIGH);  
    green = pulseIn(out, digitalRead(out) == HIGH ? HIGH : HIGH); 
    yellow = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
}

void RGB_compare()
{
    if (red >= 12 && red <= 24 && yellow >= 6 && yellow <= 18 && green >= 7 && green <= 18 && blue >= 2 && blue <= 12)
        {
        RGB_VAL == 'A';
        Serial.println(" - (BLUEEEEEEE)");
        }
    else if (red >= 10 && red <= 20 && yellow >= 7 && yellow <= 16 && green >= 6 && green <= 16 && blue >= 10 && blue <= 19)
        {
        RGB_VAL == 'B';
        Serial.println(" - (GREENNNN)");
        } 
    else if (red >= 4 && red <= 11 && yellow >= 6 && yellow <= 14 && green >= 6 && green <= 14 && blue >= 8 && blue <= 18)
        {
        RGB_VAL == 'B';
        Serial.println(" - (YELLOOOOWWW)");
        } 

    else if (red >= 6 && red <= 15 && yellow >= 25 && yellow <= 35 && green >= 25 && green <= 35 && blue >= 18 && blue <= 28)
        {
        RGB_VAL == 'C';
        Serial.println(" - (REDDDDDDDDDDD)");
        } 
    else
    {   
        George();
        //Serial.println(" IDK!");  
    }
    delay(1000); 
}
/*------------------------LINETRACKING------------------------*/
void IR5way_control() 
{   
    inputDIGITAL();
    if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 1) && (sensorValue5 == 1))
        forward;
    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 1) && (sensorValue4 == 0) && (sensorValue5 == 1))
        turnRight;
    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 0) && (sensorValue5 == 1))
        turnRight;
    else if ((sensorValue1 == 1) && (sensorValue2 == 0) && (sensorValue3 == 1) && (sensorValue4 == 1) && (sensorValue5 == 1))
        turnLeft;
    else if ((sensorValue1 == 1) && (sensorValue2 == 0) && (sensorValue3 == 0) && (sensorValue4 == 1) && (sensorValue5 == 1))
        turnLeft;
    else if ((sensorValue1 == 0) && (sensorValue2 == 0) && (sensorValue3 == 0) && (sensorValue4 == 1) && (sensorValue5 == 1))
        turnLeft;
    else if ((sensorValue1 == 0) && (sensorValue2 == 0) && (sensorValue3 == 1) && (sensorValue4 == 1) && (sensorValue5 == 1))
        turnLeft;
    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 0) && (sensorValue5 == 0))
        turnRight;
    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 0) && (sensorValue5 == 0))
        turnRight;
    else
        backward;
}

void inputDIGITAL() 
{
    sensorValue0 = digitalRead(sensorPin0);
    sensorValue1 = digitalRead(sensorPin1);
    sensorValue2 = digitalRead(sensorPin2);
    sensorValue3 = digitalRead(sensorPin3);
    sensorValue4 = digitalRead(sensorPin4);
    sensorValue5 = digitalRead(sensorPin5);
    sensorValue6 = digitalRead(sensorPin6);
    /*String KIK = " S0 = " + String ( sensorValue0 ) + " •S1= " + String ( sensorValue1 ) + " •S2= " + String ( sensorValue2) + " •S3= " + String ( sensorValue3 ) + " •S4= " + String ( sensorValue4 )+ " •S5= " + String ( sensorValue5 )+ " •S6= " + String ( sensorValue6 ) ; 
    Serial.println(KIK);
    delay(1000);*/
}
void forward() 
{
    motor1.setSpeed(spd1);
    motor2.setSpeed(spd2);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    delay(200);
    motor1.run(RELEASE);  
    motor2.run(RELEASE);
    delay (10);
    
    motor1.setSpeed(spd1*1.25);
    motor2.setSpeed(spd2*1.25);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor1.run(RELEASE);  
    motor2.run(RELEASE);
    delay(100);
    Serial.println("FORWARD");
}
  void turnRight() {
    motor1.setSpeed(spd1);
    motor2.setSpeed(spd2);
    motor1.run(FORWARD);
    motor2.run(RELEASE);
    delay(100);
    motor1.run(RELEASE);  
    motor2.run(RELEASE);
    delay (10);

    motor1.setSpeed(spd1*1.25);
    motor2.setSpeed(spd2*1.25);
    motor1.run(FORWARD);
    motor2.run(RELEASE);
    delay(100);
    motor1.run(RELEASE);  
    motor2.run(RELEASE);
   
    Serial.println("TURNRIGHT");
  }
  void turnLeft() {
    motor1.setSpeed(spd1);
    motor2.setSpeed(spd2);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    delay(100);
    motor1.run(RELEASE);  
    motor2.run(RELEASE);
    delay (10);

    motor1.setSpeed(spd1*1.25);
    motor2.setSpeed(spd2*1.25);
    motor1.run(RELEASE);
    motor2.run(FORWARD);
    delay(100);
    motor1.run(RELEASE);  
    motor2.run(RELEASE);
    delay (10);

    Serial.println("TURNLEFT");
  }
void backward(){
   motor1.setSpeed(100);
   motor2.setSpeed(100);
   motor1.run(BACKWARD);  
   motor2.run(BACKWARD); 
   delay(80);
   motor1.run(RELEASE);  
   motor2.run(RELEASE);
   delay (10);
   Serial.println("BACKWARD");
}

void George() {
  motor1.setSpeed(spd1/1.5);
  motor2.setSpeed(spd2/1.5);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(100);
  motor1.run(RELEASE);  
  motor2.run(RELEASE);
  delay (10);
  motor1.setSpeed(spd1/2);
  motor2.setSpeed(spd2/2);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(100);
  motor1.run(RELEASE);  
  motor2.run(RELEASE);
  delay (10);
  motor1.setSpeed(spd1/4);
  motor2.setSpeed(spd2/4);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(100);
  motor1.run(RELEASE);  
  motor2.run(RELEASE);
  delay (10);
  motor1.setSpeed(spd1*0);
  motor2.setSpeed(spd2*0);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(100);
  motor1.run(RELEASE);  
  motor2.run(RELEASE);
  delay (10);
}
/*------------------------LACATION------------------------*/
void stations()
{
    if (sensorValue0 == 0 && RGB_VAL == 'A')
    {
        George();
        BuzzLED();
        delay(6000); //1min
        startto(); //back
    }
    else if (sensorValue6 == 0 && RGB_VAL == 'B')
    {
        George();
        BuzzLED();
        delay(6000); //1min
        startto(); //back
    }
    else if (sensorValue0 == 0 && sensorValue6 == 0 && RGB_VAL == 'C')
    {
        George();
        BuzzLED();
        Servo_1();
        delay(6000); //1min
        startto(); //back
    }
    else 
        IR5way_control();

}
void startto()
{
    if (sensorValue0 == 0 && sensorValue1 == 1 && sensorValue2 == 1 && sensorValue3 == 1 && sensorValue4 == 1 && sensorValue5 == 1 && sensorValue6 == 0)
    {
        George();
        BuzzLED();
    } 
    else 
    IR5way_control();
}

/*------------------------SIGNAL------------------------*/
void BuzzLED()
{ 
  digitalWrite(Buzzer, HIGH);
  for (int i = 0; i < 2; i++) 
   {
    digitalWrite(Buzzer,LOW);
    delay(100);
    digitalWrite(Buzzer,HIGH);
    delay(50);
   }
  delay(1000);
}

int angle;
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
/*------------------------ULTRASONIC------------------------*/
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
   motor1.setSpeed(100);
   motor2.setSpeed(100);
   motor1.run(RELEASE);  
   motor2.run(RELEASE);
   delay (10);


     for (int i = 0; i < 2; i++) 
     {
        digitalWrite(Buzzer,LOW);
        delay(50);
        digitalWrite(Buzzer,HIGH);
        delay(50);
     }  
 }
}