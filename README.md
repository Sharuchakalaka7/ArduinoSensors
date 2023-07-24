# ArduinoSensors

As part of the "IoT Remote Sensors Project", the Arduino UNO component is responsible for handling all sensors and measurement details. The motivation is to connect MQ gas sensors to the Arduino, calibrate them initially, then host live measurement data to an [ESP Wi-Fi module](https://github.com/Sharuchakalaka7/ESPBiPort).

This software module tackles two main tasks:
1. Provides all initial configuration data
   - Network connection credentials
   - WebServer address (for the ESP module to relay data to)
   - Number of metrics measured from connected sensors
   - Cumulative measurement delay time of all sensors
   - Name and unit of each metric
2. Passes updated measurements to the ESP module readily, upon request

In the long run, the goal is to accomodate an abstract number of measurement equipment of various types and perform the same live-data-hosting. This can be extended as a C++ template library for all compatible Arduino boards.

---

Currently in v0.0.0, there is only one sensor (DHT11 Temperature/Humidity sensor) that is hard-coded as an example of the template library's use case.

> **Current Version: v0.0.0**

All Versions:
- v0.0.0: Hard-code example with DHT11 sensor
