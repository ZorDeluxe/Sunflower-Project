/*
  Sunflower Project

  Author: Zoren Dela Cruz
  Description: Monitor the sunflower environment
               for optimal growth. 
  Date: 30/10/2023
*/

#include "sensors.hpp"

Sensors sensors; // Instantiate Sensor Class

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  //set the resolution to 12 bits (0-1023)
  analogReadResolution(10);
}

void loop() {
  float soilMoisturePercentage; 
  
  soilMoisturePercentage = sensors.readSoilSensor();
  sensors.readDHTSensor();
  sensors.readUVSensor();

  // print out the values you read:
  Serial.printf("Soil Moisture Percentage= %f\n", soilMoisturePercentage);
  
  delay(500);  // delay in between reads for clear read from serial
}


