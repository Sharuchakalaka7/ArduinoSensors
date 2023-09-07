# ArduinoSensors

### Jump Ahead
--> [Description](#description)  
--> [Installation](#installation)  
--> [Version](#version)  

---




## Description

As part of the "IoT Remote Sensors Project", the Arduino UNO component is responsible for handling all sensors and measurement details. The motivation is to connect MQ gas sensors to the Arduino, calibrate them initially, then host live measurement data to an [ESP Wi-Fi module](https://github.com/Sharuchakalaka7/ESPBiPort).

This software module tackles two main tasks:
1. Provides all initial configuration data
   - Network connection credentials
   - WebServer address (for the ESP module to relay data to)
   - Number of metrics measured from connected sensors
   - Cumulative measurement delay time of all sensors
   - Name and unit of each metric
2. Passes updated measurements to the ESP module readily, upon request

In the long run, the goal is to accomodate an abstract number of measurement equipment of various types and perform the same live-data-hosting. This can be extended as a C++ template library for more Arduino boards and similar hardware devices.

---




## Installation

#### Hardware Components:
1. Ensure you have a working Arduino UNO board
2. Connect all your sensors to the Arduino UNO board appropriately
   - For instance, to connect the DHT11 Temperature and Humidity module:
      - DHT11 Data -> Arduino digital pin (e.g., pin 4)
      - DHT11 VCC -> Arduino 5V
      - DHT11 GND -> Arduino GND
4. Hook up your connectivity module: see the [ESPBiPort Installation section](https://github.com/Sharuchakalaka7/ESPBiPort#installation)
  
#### Software Components:
1. Ensure you have the Arduino IDE installed, or a similar environment
2. Download and open this repository on your environment
3. In the [`config.h`](https://github.com/Sharuchakalaka7/ArduinoSensors/blob/main/config.h) file, replace the `ssid`, `pswd`, and `serverHost` strings with your information [^1]
4. Upload/Flash the program onto the Arduino UNO
5. If you have the ESP hooked up to the Arduino board, disconnect and reconnect the power supply to synchronize

[^1]: For `serverHost`, use the IP address of the computer running the [Field Server](https://github.com/Sharuchakalaka7/FieldServer)

---




## Version

> **Current Version: v1.0.0**

Currently in v1.0.0, you can now add any number and type of sensors as long as the Arduino permits so. The code is modularized though far from perfect.

All Versions:
- v1.0.0: Base functioning project with abstract number/type of sensors
- v0.0.0: Hard-code example with DHT11 sensor
