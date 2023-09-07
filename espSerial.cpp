#include <HardwareSerial.h>
#include "espSerial.h"




EspSerial ESPSerial = EspSerial();


EspSerial::EspSerial(const uint8_t rxPin, const uint8_t txPin)
: esp(rxPin, txPin) {}


void EspSerial::begin(const long baudrate)
{
  esp.begin(baudrate);
}


String EspSerial::readLine()
{
  while (!esp.available());
  String str(esp.readStringUntil('\n'));
  str.trim();
  Serial.print("ESP --> ");
  Serial.println(str);
  return str;
}


void EspSerial::println(const String msg)
{
  Serial.println(msg);
  esp.println(msg);
}


void EspSerial::confirm(void (*delay)(unsigned long))
{
  // Convention: Empty string message means confirmation
  // delay(200);
  String msg;
  do {
    // delay(50);
    msg = readLine();
  } while (msg.length() != 0);
  esp.println(msg);
  Serial.println();
}
