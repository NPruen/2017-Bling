const int decStripPin = 11;

Adafruit_NeoPixel decStrip = Adafruit_NeoPixel(NUM_LEDS, decStripPin, NEO_GRB + NEO_KHZ800);

#define CRGB  uint32_t

#define YELLOW decStrip.Color(252, 225, 0)
//#define YELLOW decStrip.Color(255, 255, 255)
#define BLUE decStrip.Color(20, 85,251)

extern void rotatingCogsUp(CRGB colorOne, CRGB colorTwo);
extern void rotatingCogsDown(CRGB colorOne, CRGB colorTwo);
extern void cylon(CRGB colorOne, CRGB colorTwo);
extern void alternate(CRGB colorOne, CRGB colorTwo);
extern void displayColor(CRGB color);
extern void cogs(CRGB colorOne, CRGB colorTwo);
extern void expandMiddle(CRGB colorOne, CRGB colorTwo);
extern void shiftDown(CRGB colorIn);
extern void shiftUp(CRGB colorIn);
extern void expandMiddle(CRGB colorOne, CRGB colorTwo);
extern void moveCogsUp();

#define COG_SIZE 8

void decStripSetup() {
  decStrip.begin(); // Initializes the NeoPixel library
  decStrip.setBrightness(80); // Value from 0 to 100%
}

void decStripLoop(int loopCounter) {
  cogs(YELLOW, BLUE);
  rotatingCogsUp(YELLOW, BLUE);
  rotatingCogsDown(YELLOW, BLUE);
  displayColor(YELLOW);
  for (int c = 3; c > 0; c--) {
    cylon(YELLOW, BLUE);
  }
  for (int c = 20; c > 0; c--) {
    alternate(YELLOW, BLUE);
  }
  expandMiddle(YELLOW, BLUE);
}

void rotatingCogsUp(CRGB colorOne, CRGB colorTwo) {
  decStrip.show();
  for (int i = 0; i < 30; i++) {
    for (int c = 0; c < COG_SIZE; c++) {
      moveCogsUp();
      delay(100);
      decStrip.show();
    }
  }
}

void rotatingCogsDown(CRGB colorOne, CRGB colorTwo) {
  decStrip.show();
  for (int i = 0; i < 30; i++) {
    for (int c = 0; c < COG_SIZE; c++) {
      moveCogsDown();
      delay(100);
      decStrip.show();
    }
  }
}

void cylon(CRGB colorOne, CRGB colorTwo) {
  for (int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to colorOne 
    decStrip[i] = colorOne;
    // Show the leds
    decStrip.show();
    // now that we've shown the leds, reset the i'th led to black
    decStrip[i] = colorTwo;
    // Wait a little bit before we loop around and do it again
    delay(30);
  }

  // Now go in the other direction.  
  for(int i = NUM_LEDS-1; i >= 0; i--) {
    // Set the i'th led to colorTwo 
    decStrip[i] = colorTwo;
    // Show the leds
    decStrip.show();
    // now that we've shown the leds, reset the i'th led to black
    decStrip[i] = colorOne;
    // Wait a little bit before we loop around and do it again
    delay(30);
  }
}

void alternate(CRGB colorOne, CRGB colorTwo) {
  for(int i = 0; i < NUM_LEDS; i++) {
    if ((i & 1) == 0) { // For even numbered LEDs...
      decStrip[i] = colorOne;
    }
    else {
      decStrip[i] = colorTwo;
    }
    
  }
  
  decStrip.show();
  delay(200);
  
  for(int i = 0; i < NUM_LEDS; i++) {
    
    if ((i & 1) == 1) { // For odd numbered LEDs...
      decStrip[i] = colorOne;
    }
    else {
      decStrip[i] = colorTwo;
    }
    
  }
  
  decStrip.show();
  delay(200);
}

void displayColor(CRGB color) {
  for (int i=0 ; i < NUM_LEDS; i++) {
        decStrip[i] = color;
  }
  decStrip.show();
}

void cogs(CRGB colorOne, CRGB colorTwo) {
  for (int i = 0; i < NUM_LEDS; i++) {
    if ((((int) (i / COG_SIZE)) & 1) == 0) { //Alternates every 4.
      decStrip[i] = colorOne;
    }
    else {
      decStrip[i] = colorTwo;
    }
  }
}  

void moveCogsUp() {
  boolean changeColor = true;
  for (int i = 0; i < (COG_SIZE - 1); i++) {
    if (leds[i] != decStrip[i + 1]) {
      changeColor = false;
    }
  }
  if (changeColor) {
    shiftUp(decStrip[COG_SIZE]);
  }
  else {
    shiftUp(decStrip[0]);
  }
}

void moveCogsDown() {
  boolean changeColor = true;
  for (int i = (NUM_LEDS - 1); i > (NUM_LEDS - (COG_SIZE)); i--) {
    if (decStrip[i] != decStrip[i - 1]) {
      changeColor = false;
    }
  }
  if (changeColor) {
    shiftDown(decStrip[NUM_LEDS - COG_SIZE - 1]);
  }
  else {
    shiftDown(decStrip[NUM_LEDS - 1]);
  }
}

void insertMiddle(CRGB colorIn) {
  for (int i = 0; i < (NUM_LEDS/2 - 1); i++) {
    decStrip[i] = decStrip[i+1];
    decStrip[NUM_LEDS - i - 1] = decStrip[NUM_LEDS - i - 2];
  }
  if ((NUM_LEDS & 1) == 1) {
    decStrip[(NUM_LEDS - 1)/2] = colorIn;
  }
  else {
    decStrip[NUM_LEDS/2 - 1] = colorIn;
    decStrip[NUM_LEDS/2] = colorIn;
  }
}

void expandMiddle(CRGB colorOne, CRGB colorTwo) {
  displayColor(colorTwo);
  decStrip.show();
  for (int i = 0; i < 30; i++) {
    for (int c = 0; c < COG_SIZE; c++) {
      insertMiddle(colorOne);
      decStrip.show();
      delay(70);
    }
    for (int c = 0; c < COG_SIZE; c++) {
      insertMiddle(colorTwo);
      decStrip.show();
      delay(70);
    }
  }
}

//moves every led up one, and inserts colorIn at leds[0]
void shiftUp(CRGB colorIn) {
  for (int i = (NUM_LEDS - 1); i > 0; i--) {
    decStrip.setColor(i, decStrip.getColor(i-1));
  }
  decStrip[0] = colorIn;
}

//moves every led down one, and inserts colorIn at leds[(NUM_LEDS - 1)]
void shiftDown(CRGB colorIn) {
  for (int i = 0; i < (NUM_LEDS - 1); i++) { //Range: changes leds 0 - 78
    // leds[i] = leds[i + 1]; //The first led becomes the next led's color
    decStrip.setColor(i, decStrip.getColor(i+1));
  }
  //leds[(NUM_LEDS - 1)] = colorIn;
  decStrip.setColor(NUM_LEDS-1, colorIn);
}



