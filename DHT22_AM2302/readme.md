# DHT22 - AM2032 Sensor Guide for Arduino

The code is specifically written for `DHT22` sensor, which encapsulates the `AM2302` sensor and gives the output on a 3-pin interface, in contrast to `AM2302`'s 4-pin configuration.

## Definitions and Wiring

The default value for `DHTPIN` *(ln. 3)* is set to `2`. This is the digital pin connected to the DHT sensor.


* Data from sensor &rarr; `PIN2`
* Positive lead from sensor &rarr; `+5V`
* Ground lead from sensor &rarr; `GROUND`
    * Connect a 10K resistor from `PIN2` (data) to `PIN1` (power) of the sensor
    * If you are using a controller board with `3.3V` logic like an Arduino Duo, connect `PIN1` &rarr; `3.3V` instead of `5V`
* Connect `PIN1` (on the left) of the sensor to `+5V`
* Connect `PIN2` of the sensor to whatever your DHTPIN is
* Connect `PIN4` (on the right) of the sensor to GROUND

## Side Notes
* Acquiring sensor data (temperature and humidity) can take up to 1/4 seconds.
* DHT library will return Celsius reading by default.

If you need to get the Fahrenheit value, you can do this by passing in `true` argument to `readTemperature` method on `DHT`. This will likely require an `isnan(fahrenheitReading)` and changing the argument of `computeHeatIndex` function's boolean (final) argument to be true, as default one is set to be Celsius instead.
```
float fahrenheitValue = dht.readTemperature(true);
...
if (isnan(humidityValue) || isnan(temperatureValue) || isnan(fahrenheitValue)) {
    Serial.println(F("Failure message"));
    return;
}

float heatIndexValue = dht.computeHeatIndex(temperatureValue, humidityValue, true); //third argument can be skipped for Celsius as defaults to false

Serial.print(heatIndexValue);
Serial.println(F("°F"));

```

Create an issue on the repository for questions.