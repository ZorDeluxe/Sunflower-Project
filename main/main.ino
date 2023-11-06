/*
  Sunflower Project

  Author: Zoren Dela Cruz
  Description: Monitor the sunflower environment
               for optimal growth. 
  Date: 30/10/2023
*/

#include "sensors.hpp"
#include "mail.hpp"

Sensors sensors; // Instantiate Sensor Class


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  //set the resolution to 12 bits (0-1023)
  analogReadResolution(10);
}

void loop() {
  
  sensors.readSoilSensor();
  sensors.readDHTSensor();
  sensors.readUVSensor();
  
  delay(500);  // delay in between reads for clear read from serial
}


