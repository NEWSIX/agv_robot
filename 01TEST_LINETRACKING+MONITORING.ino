
int enableA = 7;
int pinA1 = 6;
int pinA2 = 5;

int enableB = 2;
int pinB1 = 4;
int pinB2 = 3;

int sensor_1 , sensor_2 , sensor_3 , sensor_4 , sensor_5 ;

String tmp ;

int ADC_stabilize = 5 ;

void setup()
{
  Serial . begin ( 9600 ) ;
   
  pinMode(enableA, OUTPUT);
  pinMode(pinA1, OUTPUT);
  pinMode(pinA2, OUTPUT);

  pinMode(enableB, OUTPUT);
  pinMode(pinB1, OUTPUT);
  pinMode(pinB2, OUTPUT);
}

void loop()
{
   sensor_1 = digitalRead ( A1 ) ;
   delay ( ADC_stabilize ) ; //stabilize
   sensor_1 = digitalRead ( A1 ) ;
   delay ( ADC_stabilize ) ;

   sensor_2 = digitalRead ( A2 ) ;
   delay ( ADC_stabilize ) ;
   sensor_2 = digitalRead ( A2 ) ;
   delay ( ADC_stabilize ) ;

   sensor_3 = digitalRead ( A3 ) ;
   delay ( ADC_stabilize ) ;
   sensor_3 = digitalRead ( A3 ) ;
   delay ( ADC_stabilize ) ;

   sensor_4 = digitalRead ( A4 ) ;
   delay ( ADC_stabilize ) ;
   sensor_4 = digitalRead ( A4 ) ;
   delay ( ADC_stabilize ) ;


   sensor_5 = digitalRead ( A5 ) ;
   delay ( ADC_stabilize ) ;
   sensor_5 = digitalRead ( A5 ) ;
   delay ( ADC_stabilize ) ;
   
   tmp = " S1=" + String ( sensor_1 ) + " S2=" + String ( sensor_2 ) + " S3=" + String ( sensor_3 ) + " S4=" + String ( sensor_4 ) + " S5=" + String ( sensor_5 ) ;
   Serial . println ( tmp ) ;
   delay ( 1000 ) ; 

  enableMotors();
  analogWrite(enableA, 255);
  analogWrite(enableB, 255);


  if ((sensor_1 == 1) && (sensor_2 == 1) && (sensor_3 == 0) && (sensor_4 == 1) && (sensor_5 == 1))
    forward(1);
  else if ((sensor_1 == 1) && (sensor_2 == 1) && (sensor_3 == 1) && (sensor_4 == 0) && (sensor_5 == 1))
    turnRight(1);
  else if ((sensor_1 == 1) && (sensor_2 == 1) && (sensor_3 == 0) && (sensor_4 == 0) && (sensor_5 == 1))
    turnRight(1);
  else if ((sensor_1 == 1) && (sensor_2 == 0) && (sensor_3 == 1) && (sensor_4 == 1) && (sensor_5 == 1))
    turnLeft(1);
  else if ((sensor_1 == 1) && (sensor_2 == 0) && (sensor_3 == 0) && (sensor_4 == 1) && (sensor_5 == 1))
    turnLeft(1);
  else if ((sensor_1 == 0) && (sensor_2 == 0) && (sensor_3 == 0) && (sensor_4 == 1) && (sensor_5 == 1))
    turnLeft(250);
  else if ((sensor_1 == 0) && (sensor_2 == 0) && (sensor_3 == 1) && (sensor_4 == 1) && (sensor_5 == 1))
    turnLeft(250);
  else if ((sensor_1 == 1) && (sensor_2 == 1) && (sensor_3 == 0) && (sensor_4 == 0) && (sensor_5 == 0))
    turnRight(250);
  else if ((sensor_1 == 1) && (sensor_2 == 1) && (sensor_3 == 0) && (sensor_4 == 0) && (sensor_5 == 0))
    turnRight(250);
  else
    forward(1);

}
void enableMotors()
{
  motorAOn();
  motorBOn();
}

void disableMotors()
{
  motorAOff();
  motorBOff();
}

void forward(int time)
{
  motorAForward();
  motorBForward();
  delay(time);
}

void backward(int time)
{
  motorABackward();
  motorBBackward();
  delay(time);
}

void turnLeft(int time)
{
  motorABackward();
  motorBForward();
  delay(time);
}

void turnRight(int time)
{
  motorAForward();
  motorBBackward();
  delay(time);
}

void coast(int time)
{
  motorACoast();
  motorBCoast();
  delay(time);
}

void brake(int time)
{
  motorABrake();
  motorBBrake();
  delay(time);
}

void motorAOn()
{
  digitalWrite(enableA, HIGH);
}

void motorBOn()
{
  digitalWrite(enableB, HIGH);
}


void motorAOff()
{
  digitalWrite(enableB, LOW);
}

void motorBOff()
{
  digitalWrite(enableA, LOW);
}

void motorAForward()
{
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, LOW);
}

void motorABackward()
{
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, HIGH);
}

void motorBForward()
{
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, LOW);
}

void motorBBackward()
{
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, HIGH);
}


void motorACoast()
{
  digitalWrite(pinA1, LOW);
  digitalWrite(pinA2, LOW);
}

void motorABrake()
{
  digitalWrite(pinA1, HIGH);
  digitalWrite(pinA2, HIGH);
}

void motorBCoast()
{
  digitalWrite(pinB1, LOW);
  digitalWrite(pinB2, LOW);
}

void motorBBrake()
{
  digitalWrite(pinB1, HIGH);
  digitalWrite(pinB2, HIGH);
}
