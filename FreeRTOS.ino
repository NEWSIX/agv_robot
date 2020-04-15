#include <Arduino_FreeRTOS.h>
#include <semphr.h>  // add the FreeRTOS functions for Semaphores (or Flags).
#include<AFMotor.h>
#include <Servo.h>

// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
// It will be used to ensure only only one Task is accessing this resource at any time.
SemaphoreHandle_t xSerialSemaphore;

AF_DCMotor motor1(3);
AF_DCMotor motor2(4); //right motor
Servo servo_test;

// define two Tasks for DigitalRead & AnalogRead
void TaskDigitalRead( void *pvParameters );
void TaskAnalogRead( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  while (!Serial) {
      
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  // Semaphores are useful to stop a Task proceeding, where it should be paused to wait,
  // because it is sharing a resource, such as the Serial port.
  // Semaphores should only be used whilst the scheduler is running, but we can set it up here.
  if ( xSerialSemaphore == NULL )  // Check to confirm that the Serial Semaphore has not already been created.
  {
    xSerialSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore we will use to manage the Serial Port
    if ( ( xSerialSemaphore ) != NULL )
      xSemaphoreGive( ( xSerialSemaphore ) );  // Make the Serial Port available for use, by "Giving" the Semaphore.
  }

  // Now set up two Tasks to run independently.
  xTaskCreate(
    TaskDigitalRead
    ,  "DigitalRead"  // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    TaskAnalogRead
    ,  "AnalogRead"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );

  // Now the Task scheduler, which takes over control of scheduling individual Tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskDigitalRead( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
  /*
    DigitalReadSerial
    Reads a digital input on pin 2, prints the result to the serial monitor

    This example code is in the public domain.
  */

  // digital pin 2 has a pushbutton attached to it. Give it a name:
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

const int Buzzer ;//31

const int trigPin = 36;
const int echoPin = 38;

  // make the pushbutton's pin an input:
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

  for (;;) // A Task shall never return or exit.
  {
    // read the input pin:
    control();

    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      // We were able to obtain or "Take" the semaphore and can now access the shared resource.
      // We want to have the Serial Port for us alone, as it takes some time to print,
      // so we don't want it getting stolen during the middle of a conversion.
      // print out the state of the button:
      Serial.println(buttonState);

      xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    }

    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
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
    {   RGB = 3; //station XxX
      //Serial.println("COLOR IS : RED 4");
    } 
  else{
    RGB = 0;
    //Serial.println(" IDK!"); 
     
  }
  delay(1000); 
    }
/*----------------------------------------------------LINETRACKING-------------------------------------*/
   

void control(){
    inputDIGITAL();
  /*  
    if ((sensorValue0 == 1) || (sensorValue6 == 1)){ // detected station
      RGB_Sensor();
      a=digitalRead(Object_Sensor);
      delay(50);

      if(sensorValue0 == 1){ // left sensor
        if(a==0){// object detected
          if(RGB == 1 ){ //color 1 is start station  ,stop w8 for other color
          signal1(); 
          Serial.println(" STATION : 1 (STARTTO) ");  
          }
          else { // other colors 
            signal1();
            delay(5000);
            signal2();
            forward(200);
          }
        }
        if(a==1){// object non detected
          signal1(); //get ready
          delay(100);
        }
      }

      if(sensorValue6 == 1 && sensorValue0 == 1){ //L&R sensor detected
        if(a==0){// object detected
          if(RGB == 2 ){//color 2  ,stop w8 receive and signal
          Serial.println(" STATION : 2 ");  
          signal1();
          delay(5000); //w8 receive 5sec 
          a=digitalRead(Object_Sensor);
          if (a == 1){
            signal2();
            forward(100);
            }
          if (a == 0){
            signal1();
            delay(5000); //w8 receive 5sec 
            signal2();
            forward(100);
            }
          }
          else {
            signal2();
            forward(100);
          }
        }
        if(a==1){// object non detected
          forward(100);
        }
      }

      if(sensorValue6 == 1){ //L&R sensor detected
        if(a==0){// object detected
          if(RGB == 3 ){//color 3  ,stop w8 receive and signal
          Serial.println(" STATION : 3 ");  
          signal1();
          delay(5000); //w8 receive 5sec 
          a=digitalRead(Object_Sensor);
          if (a == 1){
            signal2();
            forward(200);
            }
          if (a == 0){
            signal1();
            delay(5000); //w8 receive 5sec 
            signal2();
            forward(200);
            }
          }
          else {
            signal2();
            forward(200);
          }
        }
        if(a==1){// object non detected
          forward(200);
        }
      }

    }
--------------------

      if(sensorValue6 == 1){ //right sensor detected
        if(RGB>=1){
          if(RGB == 1 ){
            Serial.println(" STARTTO");  
            delay(1000);
            forward(1000);
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
    

    */
    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 1) && (sensorValue5 == 1))
        forward(200);
    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 0) && (sensorValue5 == 1))
        forward(200);
    else if ((sensorValue1 == 1) && (sensorValue2 == 0) && (sensorValue3 == 0) && (sensorValue4 == 1) && (sensorValue5 == 1))
        forward(200);

    else if ((sensorValue1 == 1) && (sensorValue2 == 0) && (sensorValue3 == 1) && (sensorValue4 == 1) && (sensorValue5 == 1))
        turnLeft();
    else if ((sensorValue1 == 1) && (sensorValue2 == 0) && (sensorValue3 == 0) && (sensorValue4 == 1) && (sensorValue5 == 1))
        turnLeft();
    else if ((sensorValue1 == 0) && (sensorValue2 == 0) && (sensorValue3 == 0) && (sensorValue4 == 1) && (sensorValue5 == 1))
        turnLeft();
    else if ((sensorValue1 == 0) && (sensorValue2 == 0) && (sensorValue3 == 1) && (sensorValue4 == 1) && (sensorValue5 == 1))
        turnLeft();
    else if ((sensorValue1 == 0) && (sensorValue2 == 1) && (sensorValue3 == 1) && (sensorValue4 == 1) && (sensorValue5 == 1))
        turnLeft();
        
    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 1) && (sensorValue4 == 0) && (sensorValue5 == 1))
        turnRight();
    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 0) && (sensorValue5 == 1))
        turnRight();  
    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 0) && (sensorValue4 == 0) && (sensorValue5 == 0))
        turnRight();
    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 1) && (sensorValue4 == 0) && (sensorValue5 == 0))
        turnRight();
    else if ((sensorValue1 == 1) && (sensorValue2 == 1) && (sensorValue3 == 1) && (sensorValue4 == 1) && (sensorValue5 == 0))
        turnRight();

    else
        backward();
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
void forward(int timedelay) 
{
    motor1.setSpeed(spd1);
    motor2.setSpeed(spd2);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    delay(timedelay);
    motor1.run(RELEASE);  
    motor2.run(RELEASE);
    delay (10);
    
    motor1.setSpeed(spd1*1.25);
    motor2.setSpeed(spd2*1.25);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    delay(timedelay/2);
    motor1.run(RELEASE);  
    motor2.run(RELEASE);
    delay(10);
}
  void turnRight() {
    motor1.setSpeed(spd1);
    motor2.setSpeed(spd2);
    motor1.run(FORWARD);
    motor2.run(RELEASE);
    delay(50);
    motor1.run(RELEASE);  
    motor2.run(RELEASE);
    delay (10);

    motor1.setSpeed(spd1*1.25);
    motor2.setSpeed(spd2*1.25);
    motor1.run(FORWARD);
    motor2.run(RELEASE);
    delay(50);
    motor1.run(RELEASE);  
    motor2.run(RELEASE);
    delay (10);
  
  }
  void turnLeft() {
    motor1.setSpeed(spd1);
    motor2.setSpeed(spd2);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    delay(50);
    motor1.run(RELEASE);  
    motor2.run(RELEASE);
    delay (10);

    motor1.setSpeed(spd1*1.25);
    motor2.setSpeed(spd2*1.25);
    motor1.run(RELEASE);
    motor2.run(FORWARD);
    delay(50);
    motor1.run(RELEASE);  
    motor2.run(RELEASE);
    delay (10);
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
}

/*
void forward(int timedelay) {
  motor1.setSpeed(spd1);
  motor2.setSpeed(spd2);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(timedelay);
  motor1.run(RELEASE);  
  motor2.run(RELEASE);
  delay (10);
  
  motor1.setSpeed(spd1*1.25);
  motor2.setSpeed(spd2*1.25);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(timedelay/2);
  motor1.run(RELEASE);  
  motor2.run(RELEASE);
  delay(10);
  Serial.println("FORWARD");
}

void turnRight(int timedelay) {
  motor1.setSpeed(spd1);
  motor2.setSpeed(spd2*1.25);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(timedelay);
  motor1.run(RELEASE);  
  motor2.run(RELEASE);
  delay (10);

  motor1.setSpeed(spd1*1.25);
  motor2.setSpeed(spd2*1.5);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(timedelay/2);
  motor1.run(RELEASE);  
  motor2.run(RELEASE);
  delay (10);
  Serial.println("TURNRIGHT");
  }
void turnLeft(int timedelay) {
  motor1.setSpeed(spd1*1.25);
  motor2.setSpeed(spd2);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(timedelay);
  motor1.run(RELEASE);  
  motor2.run(RELEASE);
  delay (10);

  motor1.setSpeed(spd1*1.5);
  motor2.setSpeed(spd2*1.25);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  delay(timedelay/2);
  motor1.run(RELEASE);  
  motor2.run(RELEASE);
  delay (10);

  Serial.println("TURNLEFT");
  }
void backward(int timedelay){
  motor1.setSpeed(spd1/1.25);
  motor2.setSpeed(spd2/1.25);
  motor1.run(BACKWARD);  
  motor2.run(BACKWARD); 
  delay(timedelay);
  motor1.run(RELEASE);  
  motor2.run(RELEASE);
  delay (10);
  Serial.println("BACKWARD");
}
*/
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

void BuzzLED(){ 
  digitalWrite(Buzzer, HIGH);
  for (int i = 0; i < 2; i++) {
    digitalWrite(Buzzer,LOW);
    delay(100);
    digitalWrite(Buzzer,HIGH);
    delay(50);
   }
}

void Servo_0(){
//  for(angle = 90; angle>=1; angle--){                                
      servo_test.write(0);
//      delay(5);                       
//    } 
}
void Servo_1(){
  for(angle = 0; angle < 90; angle ++){                                
    servo_test.write(angle);
    delay(5);                       
    } 
}

/*----------------------------------------------------XXXX-------------------------------------*/










void TaskAnalogRead( void *pvParameters __attribute__((unused)) )  // This is a Task.
{

  for (;;)
  {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);

    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see if it becomes free.
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      // We were able to obtain or "Take" the semaphore and can now access the shared resource.
      // We want to have the Serial Port for us alone, as it takes some time to print,
      // so we don't want it getting stolen during the middle of a conversion.
      // print out the value you read:
      Serial.println(sensorValue);

      xSemaphoreGive( xSerialSemaphore ); // Now free or "Give" the Serial Port for others.
    }

    vTaskDelay(1);  // one tick delay (15ms) in between reads for stability
  }
}