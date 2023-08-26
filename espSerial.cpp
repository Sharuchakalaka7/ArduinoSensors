#include <HardwareSerial.h>
#include "espSerial.h"


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
  // delay(500);
}


void EspSerial::confirm()
{
  // Convention: Empty string message means confirmation
  String msg;
  do {
    msg = readLine();
    esp.println(msg);
  } while (msg.length() != 0);
  Serial.println();
}
