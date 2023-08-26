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
  
  // Metric& operator=(const Metric& metric)
  // {
  //   this->name = metric.name;
  //   this->unit = metric.unit;
  //   this->delayTime = metric.delayTime;
  //   this->measure = metric.measure;
  //   return *this;
  // }

  const char *getName() { return name; }
  const char *getUnit() { return unit; }
  long getDelay() { return delayTime; }

  float measureValue()
  {
    delay(delayTime);
    return measure();
  }
};



#endif	// _ARDUINOSENSORS_METRIC_H
