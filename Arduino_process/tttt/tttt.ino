int Relay = 8;
int led = 11;

void setup() {
  pinMode(Relay, OUTPUT);
  pinMode(led, OUTPUT);
}
void loop() {
  digitalWrite(Relay, LOW);
  digitalWrite(led, HIGH);
  delay(3000);
  digitalWrite(Relay, HIGH);
  digitalWrite(led, LOW);
  delay(3000);
}
