#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 150

#include "DecorativeStrip.h"
#include "DirectionalStrip.h"

int loopCounter = 0;

void setup() {
  decStripSetup();
  decStripSetup1();
}

void loop() {
  decStripLoop(loopCounter);
  decStripLoop1(loopCounter);
  loopCounter++;
  if(loopCounter > NUM_LEDS) {
    loopCounter = 0;
  }
}

