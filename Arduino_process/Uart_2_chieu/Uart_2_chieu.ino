#define led 12
#define SW1 8
#define SW2 10
#define ENA 5 //define Enable Pin
#define DIR 6 //define Direction pin
#define PUL 7 //define Pulse pin

int flag1 = 0; //Cờ quay thuận
int flag2 = 0; //Cờ quay nghịch
int uart_flag = 0;

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


void setup() 
{
  Serial.begin(115200);
  init_stepper();
  init_SW();
  while(!Serial)
  {
;
  }
}

void loop() 
{        
    int  a = digitalRead(SW1);
    int  b = digitalRead(SW2);
    char buffer[16];
    int c = 0; //sent uart to jetson
    int d = 0; //Receive from Jetson
    int size = Serial.readBytesUntil('\n', buffer, 13);
    if(Serial.available()>0)
    {

//       size = Serial.readString();
      if (buffer[0] == '1')
      {
      //  Serial.print("Receive from jetson: ");
      //  Serial.println(buffer[0]);
        d = 1;
      }
      if (buffer[0] == '2')
      {
        d = 2;
      }
    }
    
     if (d == 1)   //Lưới đang ở Vị trí A
      {
//        Serial.print("flag d: ");
//        Serial.println(d);
        forward_steps(200);
        digitalWrite(led, HIGH);
        flag1 = 1;
      }
  
//     if ((flag1 == 1) && (a == HIGH) && (b == HIGH)) //Lưới xoay từ Vị trí A qua B
//      {
//        forward_steps(50);
//        digitalWrite(led, HIGH);
//        Serial.print("Lưới xoay từ Vị trí A qua B ! ");
//        delay(1000);
//      }

//      if ((a == HIGH) && (b == LOW)) // Lưới đang ở vị trí B
//      {
//        Serial.print("Lưới đang ở vị trí B ");
//        delay(10000);
//        flag2 = 1;
//        backward_steps(50); //Sau 10s, Lưới quay về vị trí A
//      }
//  
//      if ((flag2 == 1) && (b == HIGH)) // Lưới quay từ vị trí B về lại vị trí A
//      {
//        backward_steps(50);  
//        flag2 == 2;
//        Serial.print("Lưới quay từ vị trí B về lại vị trí A ");
//      }
//
//      if ((a == LOW) && (flag2 == 2)) 
//      {
//        Stop_state();
//        uart_flag = 1;
//      }
//      
//      if (buffer[0] == '2')
//      {
//        Serial.println("Stop");
//        Stop_state();
//      }
//    if (uart_flag == 1)
//    {
//      c = 0;
//      Serial.print(c);
//    }
}
