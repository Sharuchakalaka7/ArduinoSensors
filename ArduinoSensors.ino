#include "control.h"

// Sensor class includes
#include <DHT11.h>
//#include <MQ_Unified.h>




/* Define Measurement Callback Functions */
/* Note: do not deal with measurement delays inside callback functions */

float measureTemperature(bool doMeasureTemperature = true)
{
  static const uint8_t dht11Pin = 4;
  static DHT11 dht11(dht11Pin);
  if (doMeasureTemperature) return dht11.readTemperature();
  else                      return dht11.readHumidity();
}

float measureHumidity()
{
  return measureTemperature(false);
}

float measureAmmoniaTest()
{
  return random(1000);
}

// more callback functions as needed




/* Main procedures - only setup() will ever change */

Control &control = getControl();

void setup()
{
  control.addMetric("Temperature", "C", 1000, measureTemperature);
  control.addMetric("Humidity", "%", 1000, measureHumidity);
  control.addMetric("Ammonia", "ppm", 1000, measureAmmoniaTest);
  control.begin(delay);
}

void loop()
{
  control.loop();
}








// /* Initial Configuration Functions */

// void initSerial(const long baudRate = 115200)
// {
//   // Initialize all serial communications
//   Serial.begin(baudRate);
//   ESPSerial.begin(baudRate);
// }

// void initMetrics()
// {
//   // Initialize all wanted metrics/measurements
//   metrics.add(Metric("Temperature", "C", 1000, measureTemperature));
//   metrics.add(Metric("Humidity", "%", 1000, measureHumidity));
// }

// void sendNetworkInfo()
// {
//   // Send network credentials to ESP module
//   ESPSerial.println("ssid");
//   ESPSerial.println("pswd");
//   ESPSerial.confirm(delay);
// }

// void sendServerInfo()
// {
//   // Send Web Server pathway to ESP module
//   ESPSerial.println("serverHost");
//   ESPSerial.println("serverPort");
//   ESPSerial.println("serverPath");
//   ESPSerial.confirm(delay);
// }

// void sendMetricMeta()
// {
//   // Calculate total measurement delay
//   long totalDelay = 0;
//   for (int i = 0; i < metrics.getSize(); ++i)
//     totalDelay += metrics[i].getDelay();

//   // Send number of metrics and accumlated measurement delay time (+50 ms default)
//   ESPSerial.println(String(metrics.getSize()));
//   ESPSerial.println(String(totalDelay));
//   ESPSerial.confirm(delay);
// }

// void sendMetricInfo()
// {
//   // Send each metric name and unit to ESP module
//   for (int i = 0; i < metrics.getSize(); ++i)
//   {
//     ESPSerial.println(metrics[i].getName());
//     ESPSerial.println(metrics[i].getUnit());
//   }
//   ESPSerial.confirm(delay);
// }




// /* Continuous Data Measurement Functions */

// void sendMeasurements()
// {
//   ESPSerial.confirm(delay);

//   for (int i = 0; i < metrics.getSize(); ++i)
//     ESPSerial.println(String(metrics[i].measureValue()));
// }




// /* Setup and Loop Functions */

// void setup()
// {
//   unsigned long setupDelay = 0;
//   initSerial();
//   initMetrics();
  
//   sendNetworkInfo();
//   delay(setupDelay);
//   sendServerInfo();
//   delay(setupDelay);

//   sendMetricMeta();
//   delay(setupDelay);
//   sendMetricInfo();
//   delay(setupDelay);
// }


// void loop()
// {
//   Serial.println('\n');
//   Serial.println("================================\n");
//   sendMeasurements();
//   delay(1000);
// }
