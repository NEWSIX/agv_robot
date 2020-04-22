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

long duration;
int distance;
int angle;

const int Buzzer = 31;
const int trigPin = 36;
const int echoPin = 38;

// define two tasks for Blink & AnalogRead
void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  // Now set up two tasks to run independently.
  xTaskCreate(
    TaskBlink
    ,  "Blink"   // A name just for humans
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

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  pinMode(Buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
   for (;;)
  {
    
   Ultrasonic(); 
  }
}

void TaskAnalogRead(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
 servo_test.attach(10);

  for (;;)
  {
    Servo_1();
    vTaskDelay(10);
    Servo_0();
    
  }
}

/*----------------------------------------------------Ultrasonic-------------------------------------*/
void Ultrasonic() {
  digitalWrite(trigPin,HIGH);
   vTaskDelay(5);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.println(distance);
    if (distance <= 10){
      BuzzLED();
    }
    else{
    }
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
   vTaskDelay(5);                       
} 
}
void Servo_1(){
  for(angle = 0; angle < 90; angle ++){                                
    servo_test.write(angle);
    vTaskDelay(5);                       
    } 
}
