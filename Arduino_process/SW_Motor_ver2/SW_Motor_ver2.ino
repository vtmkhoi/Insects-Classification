/*
   Combine SW and Stepped Motor
*/
#define ENA 5 //define Enable Pin
#define DIR 6 //define Direction pin
#define PUL 7 //define Pulse pin
#define SW1 8 //define forward SWitch
#define SW2 10 //define backward SW

int flag1 = 0; //Cờ quay thuận
int flag2 = 0; //Cờ quay nghịch

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

void Stop_state() //Khối lệnh dừng
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

void forward_steps(uint16_t speed) //Khối lệnh quay thuận
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

void backward_steps(uint16_t speed) //Khôi lệnh quay nghịch
{
    digitalWrite(DIR,LOW);
    digitalWrite(ENA,HIGH);
  for (int i = 0; i < 1; i++)
  {
    digitalWrite(PUL,HIGH);
    delayMicroseconds(speed);
    digitalWrite(PUL,LOW);
    delayMicroseconds(speed);
  }
}

void loop() 
{
  int a = digitalRead(SW1); //Read data from switch 1
  int b = digitalRead(SW2); //Read data from switch 2
  if((a == LOW) && (b == HIGH)) //Lưới đang ở Vị trí A
  {
    forward_steps(50);
    flag1 = 1;
  }
  
   if ((a==HIGH) && (b == HIGH) && (flag1 == 1)) //Lưới xoay từ Vị trí A qua B
  {
    forward_steps(50);
  }

  if ((a == HIGH) && (b == LOW)) // Lưới đang ở vị trí B
  {
    delay(5000);
    Serial.print("Chờ 5s");
    flag2 = 1;
  }
  
  if ((flag2 == 1) && (b == HIGH) && (a == HIGH)) // Lưới quay từ vị trí B về lại vị trí A
  {
    backward_steps(50); 
  }
//
//  if((flag == 2) && (a == LOW))
//  {
//    Stop_state();
//  }
}
