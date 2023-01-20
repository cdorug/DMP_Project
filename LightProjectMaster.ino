#include <Adafruit_NeoPixel.h>
// include I2C library
#include <Wire.h>

//#include <LiquidCrystal.h>
//LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define PIN 6
#define NUMPIXELS 12

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

float readTemp = 0;
int redVal = 0;
int blueVal = 0;
float minTemp = -40.0;
float maxTemp = 40.0;

String dataString = "";

void setup() {
  pixels.begin();
  // Start i2C as master 
  Wire.begin();
  Serial.begin(9600);
}

void loop(){

  String dataString = "";
  float readTemp = 0.0F;
  
  Wire.requestFrom(8, 7);
  
  while (Wire.available()) {
    char c = Wire.read();
    dataString = dataString + c;
  }
  
  readTemp = dataString.toFloat();
  Serial.write("I am receiving this temperature: ");
  Serial.println(readTemp);
  
  // set the color
  redVal = 255 / (maxTemp - minTemp) * (readTemp - minTemp);
  blueVal = 255 / (maxTemp - minTemp) * (maxTemp - readTemp);
  
  for(int i = 0; i < NUMPIXELS; i ++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(redVal, 0, blueVal));
    pixels.show();   // Send the updated pixel colors to the hardware.
  }
  
  delay(500);
}
