#include<AFMotor.h>
AF_DCMotor motor1(3);
AF_DCMotor motor2(4); //right motor

int spd1 = 130;
int spd2 = 130;
const int sensorPin0 = 52;
const int sensorPin1 = 48;
const int sensorPin2 = 46;
const int sensorPin3 = 44;
const int sensorPin4 = 42;
const int sensorPin5 = 40;
const int sensorPin6 = 22;

int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;
int sensorValue5 = 0;

int sensorValue0 = 0;
int sensorValue6 = 0;

int Object_Sensor = 33;

const int s0 = 51;  
const int s1 = 49;  
const int s2 = 45;  
const int s3 = 47;  
const int out = 43;   
int red = 0;  
int green = 0;  
int blue = 0;
int yellow = 0;  
int RGB=0;

int station = 0 ;
int a;
    
void setup()   
{  
  Serial.begin(9600); 

  pinMode(INPUT,Object_Sensor);

  pinMode(INPUT, sensorPin1);
  pinMode(INPUT, sensorPin2);
  pinMode(INPUT, sensorPin3);
  pinMode(INPUT, sensorPin4);
  pinMode(INPUT, sensorPin5);
  pinMode(INPUT, sensorPin0);
  pinMode(INPUT, sensorPin6);

  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);  
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, HIGH);  

}  
    
void loop() 
{  
control();
}  

/*----------------------------------------------------RGB-------------------------------------*/

void RGB_Sensor()
{ 
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);  
  red = pulseIn(out, digitalRead(out) == LOW ? LOW : HIGH);  
  digitalWrite(s3, HIGH);  
  blue = pulseIn(out, digitalRead(out) == LOW ? HIGH : HIGH);  
  digitalWrite(s2, HIGH);  
  green = pulseIn(out, digitalRead(out) == HIGH ? HIGH : HIGH); 
  yellow = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  

  if (red >= 12 && red <= 24 && yellow >= 6 && yellow <= 18 && green >= 7 && green <= 18 && blue >= 2 && blue <= 12)
    {   RGB = 1; //station = 1
      Serial.println("COLOR IS : BLUE 1");
    }
  else if (red >= 10 && red <= 20 && yellow >= 7 && yellow <= 16 && green >= 6 && green <= 16 && blue >= 10 && blue <= 19)
    {   RGB = 2; //station = 2
      Serial.println("COLOR IS : GREEN 2");
    } 
  else if (red >= 4 && red <= 11 && yellow >= 6 && yellow <= 14 && green >= 6 && green <= 14 && blue >= 8 && blue <= 18)
    {   RGB = 3; //station = 3
      Serial.println("COLOR IS : YELLOW 3");
    } 

  else if (red >= 6 && red <= 15 && yellow >= 25 && yellow <= 35 && green >= 25 && green <= 35 && blue >= 18 && blue <= 28)
    {   RGB = 4; //station XxX
      Serial.println("COLOR IS : RED 4");
    } 
  else{
    RGB = 0;
    Serial.println(" IDK!"); 
     
  }
  delay(1000); 
    }
/*----------------------------------------------------LINETRACKING-------------------------------------*/
   

void control(){
    inputDIGITAL();
    
    if ((sensorValue0 == 1) || (sensorValue6 == 1)){ // detected station
      RGB_Sensor();

      if(sensorValue0 == 1){ // left sensor
        a=digitalRead(Object_Sensor);
        Serial.println(a);
        delay(50);
        if(a==0){// object detected
          forward(1000);
        }
      }

      if(sensorValue6 == 1){ //right sensor
        if(RGB>=1){
          if(RGB == 1 ){
            Serial.println(" STARTTO");  
            delay(1000);
            forward(1000);
            station = 1;
          }
          if(RGB == 2 ){
            Serial.println(" Station : 1");
            delay(1000);
            forward(1000);
          }
          if(RGB == 3){
            Serial.println(" Station : 2");
            delay(1000);
            forward(1000);
          }
          if(RGB == 4){
            Serial.println(" Station : 3"); 
            delay(1000);
            forward(1000);
          }
        }    
        if(RGB<1){
          Serial.println(" No Detected ");  
          forward(1);
        }
      }
    }

    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 1) && (sensorValue5 == 1))
        forward(1);
    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 0) && (sensorValue5 == 1))
        forward(1);
    else if ((sensorValue1 == 1) && (sensorValue2 == 0) && (sensorValue3 == 0) && (sensorValue4 == 1) && (sensorValue5 == 1))
        forward(1);

    else if ((sensorValue1 == 1) && (sensorValue2 == 0) && (sensorValue3 == 1) && (sensorValue4 == 1) && (sensorValue5 == 1))
        turnLeft(1);
    else if ((sensorValue1 == 1) && (sensorValue2 == 0) && (sensorValue3 == 0) && (sensorValue4 == 1) && (sensorValue5 == 1))
        turnLeft(1);
    else if ((sensorValue1 == 0) && (sensorValue2 == 0) && (sensorValue3 == 0) && (sensorValue4 == 1) && (sensorValue5 == 1))
        turnLeft(1);
    else if ((sensorValue1 == 0) && (sensorValue2 == 0) && (sensorValue3 == 1) && (sensorValue4 == 1) && (sensorValue5 == 1))
        turnLeft(1);
    else if ((sensorValue1 == 0) && (sensorValue2 == 1) && (sensorValue3 == 1) && (sensorValue4 == 1) && (sensorValue5 == 1))
        turnLeft(1);
        
    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 1) && (sensorValue4 == 0) && (sensorValue5 == 1))
        turnRight(1);
    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 0) && (sensorValue5 == 1))
        turnRight(1);  
    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 0) && (sensorValue5 == 0))
        turnRight(1);
    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 1) && (sensorValue4 == 0) && (sensorValue5 == 0))
        turnRight(1);
    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 1) && (sensorValue4 == 1) && (sensorValue5 == 0))
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
  sensorValue0 = digitalRead(sensorPin0);
  sensorValue6 = digitalRead(sensorPin6);
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
  motor2.setSpeed(spd2*1.25);
  motor1.run(FORWARD);
  motor2.run(RELEASE);
  delay(70);
  motor1.run(RELEASE);  
  motor2.run(RELEASE);
  delay (10);

  motor1.setSpeed(spd1*1.25);
  motor2.setSpeed(spd2*1.5);
  motor1.run(FORWARD);
  motor2.run(RELEASE);
  delay(50);
  motor1.run(RELEASE);  
  motor2.run(RELEASE);
   
  Serial.println("TURNRIGHT");
  }
void turnLeft(int timedelay) {
  motor1.setSpeed(spd1*1.25);
  motor2.setSpeed(spd2);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(70);
  motor1.run(RELEASE);  
  motor2.run(RELEASE);
  delay (10);

  motor1.setSpeed(spd1*1.5);
  motor2.setSpeed(spd2*1.25);
  motor1.run(RELEASE);
  motor2.run(FORWARD);
  delay(50);
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
  delay(50);
  motor1.run(RELEASE);  
  motor2.run(RELEASE);
  delay (10);
  Serial.println("BACKWARD");
}

/*----------------------------------------------------XXXX-------------------------------------*/