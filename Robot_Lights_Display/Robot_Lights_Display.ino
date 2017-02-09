#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 150

#include "DecorativeStrip.h"
#include "DirectionalStrip.h"

int loopCounter = 0;

void setup() {
  decStripSetup();
  dirStripSetup();
}

void loop() {
  decStripLoop(loopCounter);
  dirStripLoop(loopCounter);
  loopCounter++;
  if(loopCounter > NUM_LEDS)
    loopCounter = 0;
}
