# ArduinoSensors

This module when flashed to the Arduino UNO should handle one task mainly: **handle data read from sensors**. Given the sensor type (class), Dpin, and data parameters, there will be a template library that handles any sensor abstractly given proper hardware connection is made. This template library will be useful to converge all communication to the ESP under one convention.

Currently in v0.0.0, there is only one sensor (DHT11 Temperature/Humidity sensor) that is hard-coded as an example of the template library's use case.

> **Current Version: v0.0.0**

All Versions:
- v0.0.0: Hard-code example with DHT11 sensor
