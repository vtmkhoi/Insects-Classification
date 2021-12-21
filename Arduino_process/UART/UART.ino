#define led 12
#define SW1 8
#define SW2 10
#define PUL 7
#define DIR 6
#define ENA 5

void init_SW()
{
  pinMode (SW1, INPUT);
  pinMode (SW2, INPUT);
}

void init_stepper()
{
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  pinMode (ENA, OUTPUT);
}

void forward_steps(uint16_t speed) //Khối lệnh quay thuận
{
  digitalWrite(DIR, HIGH); //Quay cung chieu kim dong ho
  digitalWrite(ENA, HIGH);
  for (int i = 0; i < 6400; i++)
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
  for (int i = 0; i < 6400; i++)
  {
    digitalWrite(PUL,HIGH);
    delayMicroseconds(speed);
    digitalWrite(PUL,LOW);
    delayMicroseconds(speed);
  }
}

void Stop_state(uint16_t speed) //Khối lệnh dừng
{
    digitalWrite(DIR,LOW);
    digitalWrite(ENA,HIGH);
  for (int i=0; i<0; i++)
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
  init_SW();
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  while (!Serial) 
  {
    ;
  }
}

void loop() 
{
  char buffer[16];
  int  a = digitalRead(SW1);
  if (a == HIGH)
  {
    a = 1; //a = 1 là không có tác động lên SW
  }
  else
  {
    a = 0; // a = 0 là có tác động nhấn lên SW
  }
  int  b = digitalRead(SW2);
    if (b == HIGH)
  {
    b = 1;
  }
  else
  {
    b = 0;
  }
  int d = 0;
  int flag = 0;
  if(Serial.available()>0)
  {
    int size = Serial.readBytesUntil('\n', buffer, 13);
    if (buffer[0] == '1')
    {
      d = 1;
    }
  }
      if ((d == 1) && (a == 0))
      {
        if(b == 0)
        {
          backward_steps(200);
          digitalWrite(led, HIGH);
        }
        forward_steps(200);
      }

//      if (b == 0)
//      {
//        backward_steps(200);
//        delay(5000);
//        flag = 1;
//        digitalWrite(led, HIGH);
//        Serial.print(flag);
//      }

//      if (flag == 1)
//      {
//        forward_steps(200);
//        digitalWrite(led, HIGH);
//      }
    }
//    if (buffer[0] == '0')
//    {
//      digitalWrite(led, LOW);
//    }
//  }
//}



/*Code gửi từ arduino qua jetson
 * #define led 12
#define SW 8

int i = 0;

void setup() 
{
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(SW, INPUT);
  while(!Serial)
  {
    ;
  }
}

void loop() 
{
 // Serial.println("State: ");
  i = digitalRead(SW);
    if (digitalRead(SW) == HIGH)
    {
      i = 1;
      //Serial.println(i);
    }
    if (digitalRead(SW) == LOW)
    {
      i = 0;
      //Serial.println(i);
    }
    delay(1000);
}
 */
