#ifndef _ARDUINOSENSORS_ESPSERIAL_H
#define _ARDUINOSENSORS_ESPSERIAL_H

#include <SoftwareSerial.h>

class EspSerial
{
  SoftwareSerial esp;
 public:
  EspSerial(const uint8_t rxPin = 2, const uint8_t txPin = 3);
  void begin(const long);

  /* ESPSerial decorated interface */
  String readLine();
  void println(const String);
  void confirm(void (*)(unsigned long));
};

extern EspSerial ESPSerial;

#endif // _ARDUINOSENSORS_ESPSERIAL_H