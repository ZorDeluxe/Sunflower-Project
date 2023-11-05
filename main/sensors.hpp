/*
  sensor.hpp

  Author: Zoren Dela Cruz
  Description: Grabs sensor readings from
               LM393 and DHT11 sensors
  Date: 31/10/2023
*/

#pragma once

class Sensors {
  public:

  // Default constructor
  Sensors();

  // Destructor
  ~Sensors();

  // Soil Sensor Readings
  float readSoilSensor();

  // DHT Sensor Readings
  void readDHTSensor();

  // UV Sensor Readings
  void readUVSensor();

};
