int outpin = 8;
void setup() {
  pinMode(outpin,INPUT);
  Serial.begin(9600);
}

void loop() {
  while (digitalRead(outpin) == 1){
    Serial.println("Empty");
    delay(500);
  }
    Serial.println("NO-Empty");
    delay(500);
}
