#include <Arduino_FreeRTOS.h> 
#include<AFMotor.h>
#include <Servo.h>

AF_DCMotor motor1(3);
AF_DCMotor motor2(4); //right motor
Servo servo_test;

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

int a;
int newsix=0;
int mdelay=300;

const int Buzzer = 31;
const int trigPin = 36;
const int echoPin = 38;
long duration;
int distance;
/*----------------------------------------------------DEFINE-------------------------------------*/

void taskUltra( void *pvParameters );
void taskZutto( void *pvParameters );

void setup() {
  Serial.begin(9600);
  xTaskCreate(
    taskUltra
    ,  "task1"   
    ,  128  
    ,  NULL
    ,  3  
    ,  NULL );
  xTaskCreate(
    taskZutto
    ,  "task2"
    ,  128  
    ,  NULL
    ,  2  
    ,  NULL );
vTaskStartScheduler();
}
void loop()
{
}
void taskUltra(void *pvParameters)  {
  (void) pvParameters;
  pinMode(Buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  servo_test.attach(10);
   for (;;)
    {
      Ultrasonic(); 
    }
}

void taskZutto(void *pvParameters)  
 {
  (void) pvParameters;
{   
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

  pinMode(Buzzer, OUTPUT);
  servo_test.attach(10);

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  for (;;)
    {
      control();
    }
 }
}
/*----------------------------------------------------Ultrasonic-------------------------------------*/
void Ultrasonic(){
  digitalWrite(trigPin,HIGH);
  vTaskDelay(50 / portTICK_PERIOD_MS);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.println(distance);
    if (distance <= 10){
      BuzzLED();
    }
    else;
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
    {   RGB = 1; //station = 1 STARTTO
      //Serial.println("COLOR IS : BLUE 1");
    }
  else if (red >= 10 && red <= 20 && yellow >= 7 && yellow <= 16 && green >= 6 && green <= 16 && blue >= 10 && blue <= 19)
    {   RGB = 2; //station = 2
      //Serial.println("COLOR IS : GREEN 2");
    } 
  else if (red >= 4 && red <= 11 && yellow >= 6 && yellow <= 14 && green >= 6 && green <= 14 && blue >= 8 && blue <= 18)
    {   RGB = 3; //station = 3
      //Serial.println("COLOR IS : YELLOW 3");
    } 

  else if (red >= 6 && red <= 15 && yellow >= 25 && yellow <= 35 && green >= 25 && green <= 35 && blue >= 18 && blue <= 28)
    {   RGB = 4; //station XxX
      //Serial.println("COLOR IS : RED 4");
    } 
  else{
    RGB = 0;
    //Serial.println(" IDK!"); 
     
  }
  vTaskDelay(100 / portTICK_PERIOD_MS);
}
/*----------------------------------------------------LINETRACKING-------------------------------------*/
   

void control(){
  inputDIGITAL();
  
  if ((sensorValue0 == 1) || (sensorValue6 == 1)){ // detected station
    stationcompare();
    }
    
  else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 1) && (sensorValue5 == 1))
    forward(100);
  else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 0) && (sensorValue5 == 1))
    forward(100);
  else if ((sensorValue1 == 1) && (sensorValue2 == 0) && (sensorValue3 == 0) && (sensorValue4 == 1) && (sensorValue5 == 1))
    forward(100);
    
  
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

void stationcompare(){
  a=digitalRead(Object_Sensor);
  vTaskDelay(50 / portTICK_PERIOD_MS);

  if ((sensorValue0 == 1) && (sensorValue6 == 0)){
    RGB_Sensor();
    if(a==0){// object detected
      if(RGB == 1 ){ //color 1 is start station  ,stop w8 for other color
      signal1();
      vTaskDelay(100 / portTICK_PERIOD_MS);
      //Serial.println(" STATION : 1 (STARTTO) ");  
      }
      else{ // other colors 
        signal1();
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        signal2();
        forward(mdelay);
        newsix=1;
      }
    }
    else if(a==1){// object non detected
      signal1(); //get ready
    }
  }

  else if ((sensorValue0 == 0) && (sensorValue6 == 1)){
    if (newsix == 1 ){
      RGB_Sensor();
      a=digitalRead(Object_Sensor);
      if(RGB == 0){
        forward(mdelay);
        newsix=newsix+1;
      }
      if(a==0){// object detected
        if(RGB == 2){
          signal1();
          vTaskDelay(5000 / portTICK_PERIOD_MS); //w8 receive 5sec 
          a=digitalRead(Object_Sensor);
          if (a == 1){
            signal2();
            forward(mdelay);
            newsix=newsix+1;
            }
          else if (a == 0){
            signal1();
            vTaskDelay(5000 / portTICK_PERIOD_MS); //w8 receive 5sec 
            signal2();
            forward(mdelay);
            newsix=newsix+1;
            }
        }
        else {
          forward(mdelay);
          newsix=newsix+1;
        }
      }
      else if (a==0){// object non detected 
        forward(mdelay);
        newsix=newsix+1;
      }  
    } 

    else if (newsix == 2 ){
      RGB_Sensor();
      a=digitalRead(Object_Sensor);
      if(RGB == 0){
        forward(mdelay);
        newsix=newsix+1;
      }
      if(a==0){// object detected
        if(RGB == 3){
          signal1();
          vTaskDelay(5000 / portTICK_PERIOD_MS); //w8 receive 5sec 
          a=digitalRead(Object_Sensor);
          if (a == 1){
            signal2();
            forward(mdelay);
            newsix=newsix+1;
            }
          else if (a == 0){
            signal1();
            vTaskDelay(5000 / portTICK_PERIOD_MS); //w8 receive 5sec 
            signal2();
            forward(mdelay);
            newsix=newsix+1;
            }
        }
        else {
          forward(mdelay);
          newsix=newsix+1;
        }
      }
      else if (a==0){// object non detected 
        forward(mdelay);
        newsix=newsix+1;
      }  
    }

    else if (newsix == 3 ){
      RGB_Sensor();
      a=digitalRead(Object_Sensor);
      if(RGB == 0){
        forward(mdelay);
        newsix=newsix+1;
      }
      if(a==0){// object detected
        if(RGB == 4){
          signal1();
          vTaskDelay(5000 / portTICK_PERIOD_MS); //w8 receive 5sec 
          a=digitalRead(Object_Sensor);
          if (a == 1){
            signal2();
            forward(mdelay);
            newsix=newsix+1;
            }
          else if (a == 0){
            signal1();
            vTaskDelay(5000 / portTICK_PERIOD_MS); //w8 receive 5sec 
            signal2();
            forward(mdelay);
            newsix=newsix+1;
            }
        }
        else {
          forward(mdelay);
          newsix=newsix+1;
        }
      }
      else if (a==0){// object non detected 
        forward(mdelay);
        newsix=newsix+1;
      }  
    }
    else {
      forward(100);
    }
  }
}

void inputDIGITAL(){
  digitalWrite(Buzzer, HIGH);
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
  vTaskDelay(timedelay / portTICK_PERIOD_MS);
  motor1.run(RELEASE);  
  motor2.run(RELEASE);
  delay(100);
}
  void turnRight(int timedelay) {
    motor1.setSpeed(spd1);
    motor2.setSpeed(spd2);
    motor1.run(FORWARD);
    motor2.run(RELEASE);
    vTaskDelay(50 / portTICK_PERIOD_MS);
    motor1.run(RELEASE);  
    motor2.run(RELEASE);
     vTaskDelay(50 / portTICK_PERIOD_MS);
    motor1.setSpeed(spd1*1.25);
    motor2.setSpeed(spd2);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
     vTaskDelay(50 / portTICK_PERIOD_MS);
    motor1.run(RELEASE);  
    motor2.run(RELEASE);
     vTaskDelay(20 / portTICK_PERIOD_MS);
  }
  void turnLeft(int timedelay) {
    motor1.setSpeed(spd1);
    motor2.setSpeed(spd2);
    motor1.run(RELEASE);
    motor2.run(FORWARD);
     vTaskDelay(50 / portTICK_PERIOD_MS);
    motor1.run(RELEASE);  
    motor2.run(RELEASE);
     vTaskDelay(50 / portTICK_PERIOD_MS);
    motor1.setSpeed(spd1);
    motor2.setSpeed(spd2*1.25);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
     vTaskDelay(50 / portTICK_PERIOD_MS);
    motor1.run(RELEASE);  
    motor2.run(RELEASE);
     vTaskDelay(20 / portTICK_PERIOD_MS);
  }
void backward(int timedelay){
   motor1.setSpeed(spd1);
   motor2.setSpeed(spd2);
   motor1.run(RELEASE);  
   motor2.run(RELEASE);
    vTaskDelay(20 / portTICK_PERIOD_MS);
   motor1.run(BACKWARD);  
   motor2.run(BACKWARD); 
    vTaskDelay(50 / portTICK_PERIOD_MS);
   motor1.run(RELEASE);  
   motor2.run(RELEASE);
    vTaskDelay(10 / portTICK_PERIOD_MS);
}

/*----------------------------------------------------Signal-------------------------------------*/

int angle=0;

void signal1(){
BuzzLED();
Servo_1();
}
void signal2(){
BuzzLED();
Servo_0();
}

/*----------------------------------------------------BUZZER SERVO-------------------------------------*/
void BuzzLED(){ 
  digitalWrite(Buzzer, HIGH);
  for (int i = 0; i < 2; i++) {
    digitalWrite(Buzzer,LOW);
     vTaskDelay(1);
    digitalWrite(Buzzer,HIGH);
     vTaskDelay(0.5);
  }
}  

void Servo_0(){
 for(angle = 90; angle>=1; angle--){                                
      servo_test.write(0);
    vTaskDelay(50 / portTICK_PERIOD_MS);                      
  } 
}
void Servo_1(){
  for(angle = 0; angle < 90; angle ++){                                
    servo_test.write(angle);
     vTaskDelay(50 / portTICK_PERIOD_MS);                       
    } 
}
/*----------------------------------------------------XXXX-------------------------------------*/
