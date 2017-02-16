
//Constants are in main file (Robot_Lights_Display)
 
Adafruit_NeoPixel dirStrip = Adafruit_NeoPixel(NUM_LEDS, dirStripPin, NEO_GRB + NEO_KHZ800);

// Color takes RGB values, from 0,0,0 up to 255,255,255
// e.g. White = (255,255,255), Red = (255,0,0);
uint8_t red = 255;    //Value from 0(led-off) to 255(). 
uint8_t green = 255; 
uint8_t blue = 0;

#define RED decStrip.Color(255, 0, 0)
#define GREEN decStrip.Color(0, 255, 0)

void dirStripSetup() {
  dirStrip.begin(); // Initializes the NeoPixel library
  dirStrip.setBrightness(80); // Value from 0 to 100%
  pinMode(dirStripControlPin, INPUT_PULLUP);
}
void dirStripLoop(int loopCounter) {
  int pinState = digitalRead(dirStripControlPin);
  if( pinState == LOW){
    for (int i=0; i<NUM_LEDS ; i++) {
      float v = ((i+loopCounter)%(NUM_LEDS / 2))/37.50;
      dirStrip.setPixelColor(i, (uint8_t)(red * v), 0, blue); 
    }
   }
  else if (pinState == HIGH){
    for(int i=0; i<150; i++){
      float v = ((150-loopCounter+i)%75)/37.50;
      dirStrip.setPixelColor(i, (uint8_t)0, (uint8_t)(green * v), blue);  
    }
  }
  dirStrip.show();
}

int iteration=0;

void updateDirStrip() {
  int pinState = digitalRead(dirStripControlPin);
  if (iteration >= NUM_LEDS) {
    iteration = 0;
  }

  if (pinState == LOW) {
      float v = ((iteration+loopCounter)%(NUM_LEDS / 2))/37.50;
      dirStrip.setPixelColor(iteration, (uint8_t)(red * v), 0, blue); 
  }
  else if (pinState == HIGH) {
      float v = ((150-loopCounter+iteration)%(NUM_LEDS / 2))/37.50;
      dirStrip.setPixelColor(iteration, (uint8_t)0, (uint8_t)(green * v), blue);  
  }

  iteration++;
  if (iteration >= NUM_LEDS) {
    dirStrip.show();
  }
}

