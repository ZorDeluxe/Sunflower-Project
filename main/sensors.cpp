/*
  sensor.cpp

  Author: Zoren Dela Cruz
  Description: Grabs sensor readings from
               LM393 and BME280 sensors
  Date: 31/10/2023
*/
#include <iostream>
#include <Wire.h>

#include "Arduino.h"
#include "sensors.hpp"
#include "DHT.h"
#include "VEML6075.h"

#define SCLPIN 22        // I2C SCL GPIO
#define SDAPIN 21        // I2C SDA GPIO
#define DHTPIN 25        // Digital pin connected to the DHT sensor


#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
VEML6075 VML(0x10, Wire);           // Optional arguments shown

// ***************************************
// Default constructor
// ***************************************
Sensors::Sensors() {
  Serial.println("Setting up sensors");

  // Initialising DHT Sensor
  dht.begin();

  // Checking UV Sensor is detected
  VML.begin(SDAPIN, SCLPIN);        // Pass your I2C numbers (defaults 21, 22 if not specified)
}

// ***************************************
// Default destructor
// ***************************************
Sensors::~Sensors() {
  std::cout << "Destroying Sensor Class \n";
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

// ***************************************
// Reads the DHT Sensor Readings
// *************************************** 
void Sensors::readDHTSensor() {

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}

// ***************************************
// Reads the UV Sensor Readings
// *************************************** 
void Sensors::readUVSensor() {
  Serial.print("UV Index: ");
  Serial.println(VML.getUVIndex());
}