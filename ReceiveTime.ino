unsigned long time;

void setup() {
  Serial.begin(9600);
}
void loop() {
  Serial.print("Time: ");
  time = millis();
  if(time > 60000){      

  }
  Serial.println(time); 
  delay(1000); 
}
