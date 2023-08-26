// Essenstial includes
#include <List.hpp>

// Sensor class includes
#include <DHT11.h>
//#include <MQ_Unified.h>

// Custom class includes
#include "ESPSerial.h"
#include "metric.h"
#include "config.h"




/*
 * Declarations available from "config.h":
 * + String ssid
 * + String pswd
 * + String serverHost
 * + const uint16_t serverPort
 * + String serverPath
 */

// Define container instances
List<Metric> metrics;
EspSerial ESPSerial;




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

// more callback functions as needed




/* Initial Configuration Functions */

void initSerial(const long baudRate = 115200)
{
  // Initialize all serial communications
  Serial.begin(baudRate);
  ESPSerial.begin(baudRate);
}

void initMetrics()
{
  // Initialize all wanted metrics/measurements
  metrics.add(Metric("Temperature", "C", 1000, measureTemperature));
  metrics.add(Metric("Humidity", "%", 1000, measureHumidity));
}

void sendNetworkInfo()
{
  // Send network credentials to ESP module
  ESPSerial.println(ssid);
  ESPSerial.println(pswd);
  ESPSerial.confirm();
}

void sendServerInfo()
{
  // Send Web Server pathway to ESP module
  ESPSerial.println(serverHost);
  ESPSerial.println(serverPort);
  ESPSerial.println(serverPath);
  ESPSerial.confirm();
}

void sendMetricMeta()
{
  // Calculate total measurement delay
  long totalDelay = 0;
  for (int i = 0; i < metrics.getSize(); ++i)
    totalDelay += metrics[i].getDelay();

  // Send number of metrics and accumlated measurement delay time (+50 ms default)
  ESPSerial.println(String(metrics.getSize()));
  ESPSerial.println(String(totalDelay));
  ESPSerial.confirm();
}

void sendMetricInfo()
{
  // Send each metric name and unit to ESP module
  for (int i = 0; i < metrics.getSize(); ++i)
  {
    ESPSerial.println(metrics[i].getName());
    ESPSerial.println(metrics[i].getUnit());
  }
  ESPSerial.confirm();
}




/* Continuous Data Measurement Functions */

void sendMeasurements()
{
  ESPSerial.confirm();

  for (int i = 0; i < metrics.getSize(); ++i)
    ESPSerial.println(String(metrics[i].measureValue()));
}




/* Setup and Loop Functions */

void setup()
{
  unsigned long setupDelay = 500;
  initSerial();
  initMetrics();
  
  sendNetworkInfo();
  delay(setupDelay);
  sendServerInfo();
  delay(setupDelay);

  sendMetricMeta();
  delay(setupDelay);
  sendMetricInfo();
  delay(setupDelay);
}


void loop()
{
  Serial.println('\n');
  Serial.println("================================\n");
  sendMeasurements();
  delay(1000);
}
