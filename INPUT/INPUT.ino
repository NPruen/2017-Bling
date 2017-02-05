/*  Arduino Tutorial - How to use an RGB LED Strip
  Dev: Michalis Vasilakis // Date 3/6/2016 // Ver 1.0
  Info: www.ardumotive.com                */

//Library
#include <Adafruit_NeoPixel.h>

//Constants
const int dinPin = 10;    // Din pin to Arduino pin 4
const int DATA_PIN = 11;
const int numOfLeds = 150; // Number of leds
const int pin = 5; 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numOfLeds, dinPin, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(numOfLeds, DATA_PIN, NEO_GRB + NEO_KHZ800);

// Color takes RGB values, from 0,0,0 up to 255,255,255
// e.g. White = (255,255,255), Red = (255,0,0);
int red = 255;    //Value from 0(led-off) to 255(). 
int green = 255; 
int blue = 0;
int pinState;
int i;
int j=0;
void setup() {
  pixels.begin(); // Initializes the NeoPixel library
  pixels.setBrightness(80); // Value from 0 to 100%
  pixels2.begin(); // Initializes the NeoPixel library
  pixels2.setBrightness(80); // Value from 0 to 100%
  pinMode(pin, INPUT_PULLUP);
}

void loop() {
 pinState = digitalRead(pin);
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus onne.
  if( pinState == LOW){
    for (i=0; i<150 ; i++) {
      float v = ((i+j)%75)/37.50;
      pixels.setPixelColor(i, pixels.Color((int)(red * v),0,blue)); 
    }
  }
  else if (pinState == HIGH){
    for(i=0; i<150; i++){
     float v = ((150-j+i)%75)/37.50;
     pixels.setPixelColor(i, pixels.Color(0,(int)(green * v),blue));  
    }
   
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  j++;
  if (j>149){
    j = 0;
  }
}
