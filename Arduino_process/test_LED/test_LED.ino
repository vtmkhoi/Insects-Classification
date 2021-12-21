#define CTHT1 8
#define CTHT2 10
#define led1 13
#define led2 12

int flag = 0;

void setup() 
{
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}

void loop() 
{
  int a = digitalRead(CTHT1); //Read data from switch 1
  int b = digitalRead(CTHT2); //Read data from switch 2
  if ((a == LOW) && ( b == HIGH)) //Lưới đang ở vị trí 1, CTHT1 đc nhấn
  {
    flag = 1;
    digitalWrite(led1, HIGH);
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
     digitalWrite(led1, LOW);
     digitalWrite(led2, HIGH);
     delay(5000);
     flag = 2;
     Serial.print("Lật lưới từ SW2 qua SW1");
     if ((b == HIGH) && (a == HIGH))
     {
      flag = 2;
      Serial.print("Lật lưới từ SW2 qua SW1 tiếp theo");
      if ( (a == LOW) && (b  == HIGH))
      {
        return 0;
      }
     }
   } 
   
   if (flag == 1)
   {
      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
      delay(500);
   }
      if (flag == 2)
   {
      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      delay(500);
   }
  }
  
