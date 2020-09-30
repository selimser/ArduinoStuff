int ledPort = 13;

void setup() {
  pinMode(ledPort, OUTPUT);
}

void loop() {
  digitalWrite(ledPort, HIGH);
  delay(1000);
  digitalWrite(ledPort, LOW);
  delay(1000);
}
