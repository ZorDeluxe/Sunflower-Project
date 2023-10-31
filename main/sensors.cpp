/*
  sensor.cpp

  Author: Zoren Dela Cruz
  Description: Grabs sensor readings from
               LM393 and BME280 sensors
  Date: 31/10/2023
*/
#include <iostream>

#include "Arduino.h"
#include "sensor.h"
 
// ***************************************
// Default constructor
// ***************************************
Sensors::Sensors() {
  std::cout << "Creating Sensor Class \n"
}

// ***************************************
// Default destructor
// ***************************************
Sensors::~Sensors() {
  std::cout << "Destroying Sensor Class \n"
}

// ***************************************
// Reads the soil moisture in percentage
// ***************************************
float Sensors::readSoilSensor() {
  int analogReading;
  const int soilSensorPin = A0;

  // Calculate the soil readings
  analogReading = analogRead(soilSensorPin);
  return (100.0 - ((analogReading / 1023.0) * 100.0));
}