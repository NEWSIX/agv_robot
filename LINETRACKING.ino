#include<AFMotor.h>
AF_DCMotor motor1(2);
AF_DCMotor motor2(4);

int spd1 = 120;
int spd2 = 120;

int sensorPin1 = 40;
int sensorPin2 = 42;
int sensorPin3 = 44;
int sensorPin4 = 46;
int sensorPin5 = 48;

int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;
int sensorValue5 = 0;

void setup() {

  pinMode(INPUT, sensorPin1);
  pinMode(INPUT, sensorPin2);
  pinMode(INPUT, sensorPin3);
  pinMode(INPUT, sensorPin4);
  pinMode(INPUT, sensorPin5);
  Serial.begin(9600);
}

void loop() {
  inputDIGITAL();
  control();
}

void control() {
  if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 1) && (sensorValue5 == 1))
    forward(1);
  else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 1) && (sensorValue4 == 0) && (sensorValue5 == 1))
    turnRight(1);
  else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 0) && (sensorValue5 == 1))
    turnRight(1);
  else if ((sensorValue1 == 1) && (sensorValue2 == 0) && (sensorValue3 == 1) && (sensorValue4 == 1) && (sensorValue5 == 1))
    turnLeft(1);
  else if ((sensorValue1 == 1) && (sensorValue2 == 0) && (sensorValue3 == 0) && (sensorValue4 == 1) && (sensorValue5 == 1))
    turnLeft(1);
  else if ((sensorValue1 == 0) && (sensorValue2 == 0) && (sensorValue3 == 0) && (sensorValue4 == 1) && (sensorValue5 == 1))
    turnLeft(1);
  else if ((sensorValue1 == 0) && (sensorValue2 == 0) && (sensorValue3 == 1) && (sensorValue4 == 1) && (sensorValue5 == 1))
    turnLeft(1);
  else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 0) && (sensorValue5 == 0))
    turnRight(1);
  else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 0) && (sensorValue5 == 0))
    turnRight(1);
  else
    backward(100);
}

void inputDIGITAL() {
  sensorValue1 = digitalRead(sensorPin1);
  sensorValue2 = digitalRead(sensorPin2);
  sensorValue3 = digitalRead(sensorPin3);
  sensorValue4 = digitalRead(sensorPin4);
  sensorValue5 = digitalRead(sensorPin5);
  Serial.print("S1 = ");
  Serial.print(sensorValue1);
  Serial.print(" ");
  Serial.print("S2 = ");
  Serial.print(sensorValue2);
  Serial.print(" ");
  Serial.print("S3 = ");
  Serial.print(sensorValue3);
  Serial.print(" ");
  Serial.print("S4 = ");
  Serial.print(sensorValue4);
  Serial.print(" ");
  Serial.print("S5 = ");
  Serial.println(sensorValue5);
}
void forward(int timedelay) {
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
  void turnRight(int timedelay) {
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
  void turnLeft(int timedelay) {
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
void backward(int timedelay){
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