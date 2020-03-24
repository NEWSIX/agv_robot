int a;
void setup() 
{
Serial.begin(9600);
pinMode(INPUT,6);
}

void loop() 
{
  a=digitalRead(6);
  Serial.println(a);
 delay(200);
}