// include I2C library
#include <Wire.h>

float resolutionADC = .0049 ; // default ADC resolution for the 5V
//reference = 0.049 [V] / unit
float resolutionSensor = .01 ; // sensor resolution = 0.01V/°C

char buff[7]; // empty array where to put the numbers going to the master
float temp = 0;

void setup() {
    // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onRequest(requestEvent); //Interrupt for handling incoming requests
}

void loop() {
  temp = readTempInCelsius(10, A0); // read temp. 10 times  
  delay(200);
}

float readTempInCelsius(int count, int pin) {
  // read temp. count times from the analog pin
  float sumTemp = 0;
  for (int i =0; i < count; i++) {
    int reading = analogRead(pin);
    float voltage = reading * resolutionADC;
    // subtract the DC offset and converts the value in
    //degrees (C)
    float tempCelsius = (voltage - 0.5) / resolutionSensor ;
    sumTemp = sumTemp + tempCelsius; // accumulates the
    //readings
  }
  return sumTemp / (float)count; // return the average value
}


void requestEvent() {
  dtostrf(temp, 7, 2, buff);
  Serial.write("Sending temperature: ");
  Serial.println(buff);
  Wire.write(buff);
}
