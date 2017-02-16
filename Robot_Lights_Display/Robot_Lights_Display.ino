#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 150

#define CRGB  uint32_t

const int dirStripPin = 10;    // Din pin to Arduino pin 4
const int dirStripControlPin = 6;
const int decStripPin = 11;

int loopCounter = 0;

void setup() {
  dirStripSetup();
  decStripSetup();
}

void loop() {
  //dirStripLoop(loopCounter);
  decStripLoop(loopCounter);
  loopCounter++;
  if(loopCounter > NUM_LEDS) {
    loopCounter = 0;
  }
}

