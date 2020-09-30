int ledPort = 13;

void setup()
{
    pinMode(ledPort, OUTPUT);
}

void loop()
{
    for (int i = 0; i < 20; i++)
    {
        digitalWrite(ledPort, HIGH);
        delay(25);
        digitalWrite(ledPort, LOW);
        delay(25);
    }
    
    delay(500);
}