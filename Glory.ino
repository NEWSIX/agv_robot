#include<AFMotor.h>
AF_DCMotor motor1(3);
AF_DCMotor motor2(4);

int spd1 = 0;
int spd2 = 0;

int sensorPin0 = 52;
int sensorPin1 = 48;
int sensorPin2 = 46;
int sensorPin3 = 44;
int sensorPin4 = 42;
int sensorPin5 = 40;
int sensorPin6 = 22;

int sensorValue0 = 0;
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;
int sensorValue5 = 0;
int sensorValue6 = 0;

String Located ,RGB;

void setup() {
  pinMode(INPUT, sensorPin0);
  pinMode(INPUT, sensorPin1);
  pinMode(INPUT, sensorPin2);
  pinMode(INPUT, sensorPin3);
  pinMode(INPUT, sensorPin4);
  pinMode(INPUT, sensorPin5);
  pinMode(INPUT, sensorPin6);
 
  Serial.begin(9600);
}

void loop() {
  inputDIGITAL();
  //control();
  
  
}

void control() {
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

void inputDIGITAL() {
  sensorValue0 = digitalRead(sensorPin0);
  sensorValue1 = digitalRead(sensorPin1);
  sensorValue2 = digitalRead(sensorPin2);
  sensorValue3 = digitalRead(sensorPin3);
  sensorValue4 = digitalRead(sensorPin4);
  sensorValue5 = digitalRead(sensorPin5);
  sensorValue6 = digitalRead(sensorPin6);
  String KIK = " S0 = " + String ( sensorValue0 ) + " •S1= " + String ( sensorValue1 ) + " •S2= " + String ( sensorValue2) + " •S3= " + String ( sensorValue3 ) + " •S4= " + String ( sensorValue4 )+ " •S5= " + String ( sensorValue5 )+ " •S6= " + String ( sensorValue6 ) ; 
  Serial.println(KIK);
  delay(1000);
}
void forward() {
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
void stations()
{
  if (sensorValue0 == 0)
    {
      Located = 'A';
    }
}

void XOXO()
{
  if ( Located == 'A' && RGB == 'A')
    {
      George();
    }
  if ( Located == 'A' && RGB == 'A')
    {
      George();
    }
}
