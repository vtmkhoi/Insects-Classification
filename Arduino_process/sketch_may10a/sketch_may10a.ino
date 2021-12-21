/*
 * Version 1 Step motor
 */
#define ENA 5 //define Enable Pin
#define DIR 6 //define Direction pin
#define PUL 7 //define Pulse pin
#define SW1 3

void init_SW()
{
  pinMode (SW1, INPUT);
}

void init_stepper()
{
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  pinMode (ENA, OUTPUT);
}
void Stop()
{
   digitalWrite(DIR,LOW);
    digitalWrite(ENA,HIGH);
  for (int i=0; i<0; i++)
  {
    digitalWrite(PUL,HIGH);
    delayMicroseconds(0);
    digitalWrite(PUL,LOW);
    delayMicroseconds(0);
  }
}
void forward_steps(uint16_t speed) 
{
    digitalWrite(DIR,HIGH);
    digitalWrite(ENA,HIGH);
  for (int i=0; i<1; i++)
  {
    digitalWrite(PUL,HIGH);
    delayMicroseconds(speed);
    digitalWrite(PUL,LOW);
    delayMicroseconds(speed);
  }
  // delay(500);
}

void backward_steps(uint16_t speed) 
{
    digitalWrite(DIR,LOW);
    digitalWrite(ENA,HIGH);
      for (int i=0; i<800; i++)
    {
      digitalWrite(PUL,HIGH);
      delayMicroseconds(speed);
      digitalWrite(PUL,LOW);
      delayMicroseconds(speed);

    }
      delay(500);
}

void microbackward_steps(uint16_t speed)
{
    digitalWrite(DIR,LOW);
    digitalWrite(ENA,HIGH);
  for (int i = 0; i < 400; i++)
  {
    digitalWrite(PUL,HIGH);
    delayMicroseconds(speed);
    digitalWrite(PUL,LOW);
    delayMicroseconds(speed);
  }
}

void setup() 
{
  init_stepper();
  Serial.begin(115200);
  while (!Serial) 
  {
    ;
  }
}

void loop(){   
  backward_steps(1000);

  }
