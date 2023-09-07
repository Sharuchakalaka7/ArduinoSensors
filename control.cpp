#include <HardwareSerial.h>
#include "config.h"
#include "control.h"
#include "espSerial.h"




bool Control::instanceExists = false;

Control& getControl()
{
  static Control control;
  return control;
}




Control::Control()
: valid(!instanceExists), setupCalled(false), delay(nullptr), metrics()
{
  instanceExists = true;
}


Control::~Control()
{
  instanceExists = false;
}


bool Control::addMetric(const char *name, const char *unit, long delayTime, float (*measure)())
{
  bool condition = (valid && !setupCalled);
  if (condition) metrics.add(Metric(name, unit, delayTime, measure));
  return condition;
}


void Control::begin(void (*delay)(unsigned long))
{
  if (!setupCalled)
  {
    setupCalled = true;
    this->delay = delay;
    unsigned long setupDelay = 0;
    initSerial();
    
    sendNetworkInfo();
    delay(setupDelay);
    sendServerInfo();
    delay(setupDelay);

    sendMetricMeta();
    delay(setupDelay);
    sendMetricInfo();
    delay(setupDelay);
  }
}


void Control::loop()
{
  if (valid && setupCalled)
  {
    Serial.println('\n');
    Serial.println("================================\n");
    sendMeasurements();
    delay(1000);
  }
}




void Control::initSerial()
{
  // Initialize all serial communications
  unsigned long baudrate = 115200;
  Serial.begin(baudrate);
  ESPSerial.begin(baudrate);

}


void Control::sendNetworkInfo()
{
  // Send network credentials to ESP module
  ESPSerial.println(ssid);
  ESPSerial.println(pswd);
  ESPSerial.confirm(delay);
}


void Control::sendServerInfo()
{
  // Send Web Server pathway to ESP module
  ESPSerial.println(serverHost);
  ESPSerial.println(serverPort);
  ESPSerial.println(serverPath);
  ESPSerial.confirm(delay);
}


void Control::sendMetricMeta()
{
  // Calculate total measurement delay
  long totalDelay = 0;
  for (int i = 0; i < metrics.getSize(); ++i)
    totalDelay += metrics[i].getDelay();

  // Send number of metrics and accumlated measurement delay time (+50 ms default)
  ESPSerial.println(String(metrics.getSize()));
  ESPSerial.println(String(totalDelay));
  ESPSerial.confirm(delay);
}


void Control::sendMetricInfo()
{
  // Send each metric name and unit to ESP module
  for (int i = 0; i < metrics.getSize(); ++i)
  {
    ESPSerial.println(metrics[i].getName());
    ESPSerial.println(metrics[i].getUnit());
  }
  ESPSerial.confirm(delay);
}




void Control::sendMeasurements()
{
  ESPSerial.confirm(delay);
  for (int i = 0; i < metrics.getSize(); ++i)
    ESPSerial.println(String(metrics[i].measureValue(delay)));
}
