/*
   Combine SW and Stepped Motor
*/
#define ENA 5 //define Enable Pin
#define DIR 6 //define Direction pin
#define PUL 7 //define Pulse pin
#define SW1 8 //define forward SWitch
#define SW2 10

int flag = 0;
void init_stepper()
{
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  pinMode (ENA, OUTPUT);
}

void init_SW()
{
  pinMode (SW1, INPUT);
  pinMode (SW2, INPUT);
}


void setup() {
  init_stepper();
  Serial.begin(9600);
  init_SW();
}

void Stop_state()
{
  digitalWrite(ENA, HIGH);
  digitalWrite(PUL, LOW);
  digitalWrite(DIR, HIGH);
}

void forward_steps(uint16_t speed)
{
  digitalWrite(DIR, HIGH); //Quay cung chieu kim dong ho
  digitalWrite(ENA, HIGH);
  for (int i = 0; i < 1; i++)
  {
    digitalWrite(PUL, HIGH);
    delayMicroseconds(speed);
    digitalWrite(PUL, LOW);
    delayMicroseconds(speed);
  }
}

void backward_steps(uint16_t speed) 
{
    digitalWrite(DIR,LOW);
    digitalWrite(ENA,HIGH);
  for (int i=0; i<1; i++)
  {
    digitalWrite(PUL,HIGH);
    delayMicroseconds(speed);
    digitalWrite(PUL,LOW);
    delayMicroseconds(speed);
  }
}

void loop() 
{
     
   if (flag == 1)
   {
    forward_steps(20);
   }
      if (flag == 2)
   {
    backward_steps(20);
   }
   
  int a = digitalRead(SW1); //Read data from switch 1
  int b = digitalRead(SW2); //Read data from switch 2

  if((a == LOW) && ( b == HIGH)) //Lưới đang ở vị trí 1, CTHT1 đc nhấn
  {
    flag = 1;
    Serial.print("Lật lưới từ SW1 qua SW2");
    if ((a == HIGH) && (b == HIGH))
    {
      flag = 1;
      Serial.print("Lật lưới từ SW1 qua SW2 tiếp theo");
      delay(1000);
    }
  }
   if ((a == HIGH) && (b == LOW))
   {
     Serial.print("Lật lưới từ SW2 qua SW1");
     delay(5000);
     flag = 2;
     backward_steps(20);
     if (flag == 2)
     {
      flag = 2;
      Serial.print("Lật lưới từ SW2 qua SW1 tiếp theo");
      if ( (a == LOW) && (b  == HIGH))
      {
        Stop_state();
        exit(0);
      }
     }
   } 
}
