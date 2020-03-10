#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define Pinout 8
int frequency = 0;
void setup() {
 pinMode(S0, OUTPUT);
 pinMode(S1, OUTPUT);
 pinMode(S2, OUTPUT);
 pinMode(S3, OUTPUT);
 pinMode(Pinout, INPUT);

 digitalWrite(S0,HIGH);
 digitalWrite(S1,HIGH);
 Serial.begin(9600);
}

void loop() {
 digitalWrite(S2,LOW);
 digitalWrite(S3,LOW);
 frequency = pulseIn(Pinout,LOW);
 frequency = map (frequency, 25,70, 255, 0);
 Serial.print("R= ");
 Serial.print(frequency);
 Serial.print(" ");
 delay(100);

 digitalWrite(S2,HIGH);
 digitalWrite(S3,HIGH);
 frequency = pulseIn(Pinout,LOW);
 frequency = map(frequency, 30,90,255,0);
 Serial.print("G= ");
 Serial.print(frequency);
 Serial.print(" ");
 delay(100);
 
 digitalWrite(S2,LOW);
 digitalWrite(S3,HIGH);
 frequency = pulseIn(Pinout,LOW);
 frequency = map(frequency, 25,70,255,0);
 Serial.print("B= ");
 Serial.print(frequency);
 Serial.println(" ");
 delay(100);


}
