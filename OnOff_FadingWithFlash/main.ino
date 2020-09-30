int ledPin = 13;

void setup() {}

void loop()
{
    for (int i = 0; i < 3; i++)
    {
        for (int fadeValue = 0; fadeValue <= 255; fadeValue += 5)
        {
            analogWrite(ledPin, fadeValue);
            delay(30);
        }

        for (int fadeValue = 255; fadeValue >= 0; fadeValue -= 5)
        {
            analogWrite(ledPin, fadeValue);
            delay(30);
        }

        if (i >= 2)
        {
            for (int j = 0; j <= 15; j++)
            {
                digitalWrite(ledPin, HIGH);
                delay(50);
                digitalWrite(ledPin, LOW);
                delay(50);
                if (j % 5 == 0)
                {
                    delay(300);
                }
            }
        }
    }
}
