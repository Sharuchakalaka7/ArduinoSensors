#ifndef _ARDUINOSENSORS_CONTROL_H
#define _ARDUINOSENSORS_CONTROL_H

#include <List.hpp>
#include "metric.h"

/* Streamline all Arduino processes into a container - helps with adding feature */
class Control
{
 public:
  Control();
  ~Control();
  /* Client interface */
  bool addMetric(const char*, const char*, long, float (*)());   // let clients add metrics dynamically
  void begin(void (*)(unsigned long));
  void loop();

 private:
  /* Setup helper functions */
  void initSerial();
  void sendNetworkInfo();
  void sendServerInfo();
  void sendMetricMeta();
  void sendMetricInfo();

  /* Loop helper functions */
  void sendMeasurements();

  /* Data members */
  bool valid;
  bool setupCalled;
  void (*delay)(unsigned long);
  List<Metric> metrics;

  /* Prevent instance co-existence and copy mechanics except possibly in cpp; keep default move mechanics */
  static bool instanceExists;
  Control(const Control&);
  Control &operator=(const Control&);
};

Control &getControl();

#endif // _ARDUINOSENSORS_CONTROL_H
