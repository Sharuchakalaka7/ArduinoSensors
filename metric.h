#ifndef _ARDUINOSENSORS_METRIC_H
#define _ARDUINOSENSORS_METRIC_H

// Container for neatly defining measurements from arbitrary sensors
class Metric
{
  const char *name;
  const char *unit;
  long delayTime;
  float (*measure)();	// Pointer to the function measuring this metric
 public:
  Metric(const char *name, const char *unit, long delayTime, float (*measure)())
  : name(name), unit(unit), delayTime(delayTime), measure(measure) {}

  const char *getName() { return name; }
  const char *getUnit() { return unit; }
  long getDelay() { return delayTime; }

  float measureValue(void (*delay)(unsigned long))
  {
    delay(delayTime);
    return measure();
  }
};



#endif	// _ARDUINOSENSORS_METRIC_H
