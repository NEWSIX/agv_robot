#include <Arduino_FreeRTOS.h> 
//https://circuitdigest.com/microcontroller-projects/arduino-freertos-tutorial1-creating-freertos-task-to-blink-led-in-arduino-uno
void TaskBlink1( void *pvParameters );
void TaskBlink2( void *pvParameters );
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  xTaskCreate(
    TaskBlink1
    ,  "task1"   
    ,  128  
    ,  NULL
    ,  3  
    ,  NULL );
  xTaskCreate(
    TaskBlink2
    ,  "task2"
    ,  128  
    ,  NULL
    ,  3  
    ,  NULL );
vTaskStartScheduler();
}
void loop()
{
}
void TaskBlink1(void *pvParameters)  {
  (void) pvParameters;
  pinMode(8, OUTPUT);
  for (;;)
  {
    Serial.println("Task1");
    digitalWrite(8, LOW);   
    vTaskDelay(10); 
    digitalWrite(8, HIGH);    
    vTaskDelay(1); 
  }
}
void TaskBlink2(void *pvParameters)  
{(void) pvParameters;
  pinMode(7, OUTPUT);
  for (;;)
  {
    Serial.println("Task2");
    digitalWrite(7, HIGH);   
    vTaskDelay(100); 
    digitalWrite(7, LOW);   
    vTaskDelay(100); 
  }
}
