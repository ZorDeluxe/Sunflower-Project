/*
  Sunflower Project

  Author: Zoren Dela Cruz
  Description: Monitor the sunflower environment
               for optimal growth. 
  Date: 30/10/2023
*/


void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  //set the resolution to 12 bits (0-1023)
  analogReadResolution(10);
}

void loop() {
  float soilMoisturePercentage; 
  
  soilMoisturePercentage = readSoilSensor();

  // print out the values you read:
  Serial.printf("Soil Moisture Percentage= %f\n", soilMoisturePercentage);
  
  delay(500);  // delay in between reads for clear read from serial
}

// ***************************************
// Reads the soil moisture in percentage
// ***************************************
float readSoilSensor() 
{
  int analogReading;
  const int soilSensorPin = A0;

  // Calculate the soil readings
  analogReading = analogRead(soilSensorPin);
  return (100.0 - ((analogReading / 1023.0) * 100.0));
}

