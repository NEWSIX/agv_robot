const int s0 = 51;  
const int s1 = 49;  
const int s2 = 45;  
const int s3 = 47;  
const int out = 43;   
int red = 0;  
int green = 0;  
int blue = 0;
int yellow = 0;  
    
void setup()   
{  
  Serial.begin(9600); 
  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);  
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, HIGH);  
}  
    
void loop() 
{  
  color(); 
  Serial.print("R Intensity:");  
  Serial.print(red, DEC);
  Serial.print(" Y Intensity : ");  
  Serial.print(yellow, DEC);   
  Serial.print(" G Intensity: ");  
  Serial.print(green, DEC);  
  Serial.print(" B Intensity : ");  
  Serial.print(blue, DEC);  
  compare();
  delay(1000);   

 }  
    
void color()  
{    
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);  
  red = pulseIn(out, digitalRead(out) == LOW ? LOW : HIGH);  
  digitalWrite(s3, HIGH);  
  blue = pulseIn(out, digitalRead(out) == LOW ? HIGH : HIGH);  
  digitalWrite(s2, HIGH);  
  green = pulseIn(out, digitalRead(out) == HIGH ? HIGH : HIGH); 
  yellow = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
}
void compare()
{
  if (red >= 12 && red <= 24 && yellow >= 6 && yellow <= 18 && green >= 7 && green <= 18 && blue >= 2 && blue <= 12)
    {
      Serial.println(" - (BLUEEEEEEE)");
    }
  else if (red >= 10 && red <= 20 && yellow >= 7 && yellow <= 16 && green >= 6 && green <= 16 && blue >= 10 && blue <= 19)
    {
      Serial.println(" - (GREENNNN)");
    } 
  else if (red >= 4 && red <= 11 && yellow >= 6 && yellow <= 14 && green >= 6 && green <= 14 && blue >= 8 && blue <= 18)
    {
      Serial.println(" - (YELLOOOOWWW)");
    } 

  else if (red >= 6 && red <= 15 && yellow >= 25 && yellow <= 35 && green >= 25 && green <= 35 && blue >= 18 && blue <= 28)
    {
      Serial.println(" - (REDDDDDDDDDDD)");
    } 
  else{
  Serial.println(" IDK!");  
  }
}
