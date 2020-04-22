int Buzzer = 31;
const int trigPin = 36;
int echoPin = 38;
long duration;
int distance;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop() {
  Ultrasonic();
}

void Ultrasonic() {
  digitalWrite(trigPin,HIGH);
  delay(5);
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
void BuzzLED(){ 
  digitalWrite(Buzzer, HIGH);
  for (int i = 0; i < newsix; i++) {
    digitalWrite(Buzzer,LOW);
    delay(100);
    digitalWrite(Buzzer,HIGH);
    delay(50);
   }
}