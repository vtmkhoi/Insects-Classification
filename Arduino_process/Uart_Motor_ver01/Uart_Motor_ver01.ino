#define led1 12    //LED debug
#define led2 10
#define SW1 2     //Limit Switch Position A
#define SW2 3     //Limit Switch Position B
#define PUL 7     //Pulse Pin for stepper motor
#define DIR 6     //Direction Pin for stepper motor 
#define ENA 5     // Enable Pin for stepper motor

int flag1 = 0;    
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;
int flag5 = 0;
int flag6 = 0;
int bientam = 0;

/*
 * Khởi tạo Switch
 */
 
void init_SW()
{
  pinMode (SW1, INPUT);
  pinMode (SW2, INPUT);
}

/*
 * Khởi tạo động cơ bước
 */
void init_stepper()
{
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  pinMode (ENA, OUTPUT);
}

/*
 * Đoạn code quay thuận chiều kim đồng hồ
 */
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

/*
 * Đoạn code quay ngược chiều kim đồng hồ
 */
void backward_steps(uint16_t speed) //Khôi lệnh quay nghịch
{
    digitalWrite(DIR,LOW);
    digitalWrite(ENA,HIGH);
  for (int i = 0; i < 800; i++)
  {
    digitalWrite(PUL,HIGH);
    delayMicroseconds(speed);
    digitalWrite(PUL,LOW);
    delayMicroseconds(speed);
  }
}

/*
 * Đoạn code quay nghịch với số bước nhỏ
 */
void microbackward_steps(uint16_t speed)
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

void Stop_state(uint16_t speed) //Khối lệnh dừng
{
    digitalWrite(DIR,LOW);
    digitalWrite(ENA,LOW);
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
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  while (!Serial) 
  {
    ;
  }
}

void loop() 
{
  char buffer[16];
  int  a = digitalRead(SW1); // a = 1: không nhấn SW, a = 0: có nhấn SW
  int  b = digitalRead(SW2); // b = 1: không nhấn SW, b = 0: có nhấn SW
  int c = 0; 
  int d = 0;
  int e = 1;
  
  /*
   * Khối nhận Uart từ Jetson
   * c = 1: Khi chụp xong 1 ảnh, gửi Buffer = '1' về arduino
   */
  if(Serial.available()>0)
  {
    int size = Serial.readBytesUntil('\n', buffer, 13);
    if (buffer[0] == '1')
    {
      c = 1;
    }
    if (buffer[0] == '2')
    {
      d = 1;
    }
  }

/*
 * Khối điều khiển step motor sau khi jetson chụp xong
 * Motor quay từ A sang B
 */
  
  if (c == 1)     //Buff[0] = '1', cho c = 1
  {
    flag1 = 1;    //Dựng cờ 1 = 1
    Serial.print("Gia tri buffer: ");
    Serial.println(buffer[0]);
  }

  if(flag1 == 1)
 // if ((flag1 == 1) && (a == LOW))   //Lấy cờ 1 và nút nhấn A làm điều kiện quay thuận
  {
    forward_steps(800);
    flag2 = 1;
  } 

  if((flag2 == 1) && (a == HIGH))
  {
    flag1 = 0;
    forward_steps(800);
    flag3 = 1;
   // flag2 = 0;
  }
/*
 * Khối điều khiển step motor dừng và quay ngược
 * Motor quay từ B về A
 */

  if((flag3 == 1) && (b == LOW))
  {
    delay(3000);
    backward_steps(1000);
    flag4 = 1;
  }

  if((flag4 == 1) && (b == HIGH))
  { 
    flag2 = 0;
    digitalWrite(led2, HIGH);
    microbackward_steps(800);
    flag5 = 1;
  }

/*
 * Khối điều khiển dừng step motor và feedback về cho jetson
 * Motor lúc này đang ở A
 */

  if((flag5 == 1) && (a == LOW) && (b == HIGH))
  {
    flag3 = 0;
    flag4 = 0;
    Stop_state(0);
    Serial.print("gửi giá trị qua Jetson: ");
    Serial.println(e);
    digitalWrite(led1, HIGH);
  }
  else
  {
    ; // Do nothing
  }

 if(d == 1)
 {
    Serial.print("Giá trị Buff lúc sau: ");
    Serial.println(buffer[0]);
    Stop_state(0);
    digitalWrite(led1, LOW);
 }
}
