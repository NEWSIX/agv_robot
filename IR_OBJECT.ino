int a;
int Object_Sensor = 33;
void setup() 
{
Serial.begin(9600);
pinMode(INPUT,Object_Sensor);
}

void loop() 
{
  a=digitalRead(Object_Sensor);
  Serial.println(a);
 delay(200);
}