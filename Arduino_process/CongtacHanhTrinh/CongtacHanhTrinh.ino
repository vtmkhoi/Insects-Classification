#define SW1 2
#define SW2 3
   
int a = 0; 
int b = 0;   

void setup() 
{
  Serial.begin(115200);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
}

void loop() {
  a = digitalRead(SW1);
  b = digitalRead(SW2);

   if (a == HIGH) //|| (b == HIGH))
   {
    Serial.print("Giá trị của A: ");
    Serial.println(a);
//    Serial.print("Giá trị của B: ");
//    Serial.println(b);    
    } 
   else 
  {
    Serial.print("Giá trị của A: ");
    Serial.println(a);
//    Serial.print("Giá trị của B: ");
//    Serial.println(b);  
  }
delay(200);// delay 1 giây
}
