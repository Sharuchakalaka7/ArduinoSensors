#include <SoftwareSerial.h>
#include <DHT11.h>




const long baudRate = 9600;
const uint8_t rxPin = 2;
const uint8_t txPin = 3;
const uint8_t dht11Pin = 4;


const String GET_STR("GET");
SoftwareSerial ESPSerial(rxPin, txPin);
DHT11 dht11(dht11Pin);




void setup()
{
  Serial.begin(baudRate);
  ESPSerial.begin(baudRate);
}




void loop()
{
  if (ESPSerial.available())
  {
    String str = ESPSerial.readStringUntil('\n');
    // Serial.print("RX --> ");
    // Serial.println(str);

    if (str.startsWith(GET_STR))
    {
      float temperature = dht11.readTemperature();
      delay(1000);
      float humidity = dht11.readHumidity();

      Serial.println("GET");
      // Serial.print("TX --> ");
      Serial.println(temperature);
      // Serial.print("TX --> ");
      Serial.println(humidity);
      
      ESPSerial.println(temperature);
      ESPSerial.println(humidity);
    }
  }
}
