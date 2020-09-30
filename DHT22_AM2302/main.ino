#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("Initialising..."));
  dht.begin();
}

void loop() {
  delay(1000); //sleep a second between readings

  float humidityValue = dht.readHumidity();
  float temperatureValue = dht.readTemperature();

  
  if (isnan(humidityValue) || isnan(temperatureValue)) { //check read failures
    Serial.println(F("ERROR: Failed to read from the sensor!"));
    return; //jump to next loop
  }

  float heatIndexValue = dht.computeHeatIndex(temperatureValue, humidityValue, false);

  Serial.print(F("Humidity: "));
  Serial.print(humidityValue);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperatureValue);
  Serial.print(F("°C "));
  Serial.print(heatIndexValue);
  Serial.println(F("°C "));  
}
