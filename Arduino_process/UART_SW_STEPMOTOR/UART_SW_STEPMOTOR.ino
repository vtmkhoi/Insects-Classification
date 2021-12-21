/*
   Combine SW and Stepped Motor
*/
#define ENA 5 //define Enable Pin
#define DIR 6 //define Direction pin
#define PUL 7 //define Pulse pin
#define SW1 3 //define forward SWitch
#define SW2 2 //define backward Switch
#define LED 13

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
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  init_SW();
  while (!Serial){
    ;
  }
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

void loop() {
  int a = digitalRead(SW1); //Read data from switch 1
  int b = digitalRead(SW2); //Read data from switch 2
  char buffer[16];
  if(Serial.available()>0)
  {
    int size = Serial.readBytesUntil('\n', buffer, 13);
  }
    if ((a == LOW) && (b == HIGH) && (buffer[0] == '1')) //Động cơ quay Theo chiều kim đồng hồ
    {
      flag = 1;
      digitalWrite(LED, HIGH);
      forward_steps(50);
    }
    else if ((a == HIGH) && (b == HIGH) && (buffer[0] == '1') && (flag = 1))
    {
      forward_steps(50);
      digitalWrite(LED, HIGH);
    }
    else 
    {
      flag = 2;
    }
    if (flag == 1)
    {
      forward_steps(50);
      digitalWrite(13,LOW);
    }
    else if (flag == 2)
    {
      backward_steps(50);
      digitalWrite(ENA, HIGH);
      digitalWrite(DIR,HIGH);
      digitalWrite(PUL,HIGH);
      digitalWrite(LED,HIGH);
    }
    else 
    {
    }
    if (buffer[0] == '0')
    {
      digitalWrite(LED, LOW);
      digitalWrite(ENA, HIGH);
      digitalWrite(DIR,HIGH);
      digitalWrite(PUL,HIGH);
      digitalWrite(LED,HIGH);
    }
      delay(50);
  }
