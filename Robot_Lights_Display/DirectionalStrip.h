
//Constants
const int dirStripPin = 10;    // Din pin to Arduino pin 4
const int dirStripControlPin = 6;

const int dirStripLEDs = 150; // Number of leds

 
Adafruit_NeoPixel dirStrip = Adafruit_NeoPixel(NUM_LEDS, dirStripPin, NEO_GRB + NEO_KHZ800);

// Color takes RGB values, from 0,0,0 up to 255,255,255
// e.g. White = (255,255,255), Red = (255,0,0);
uint8_t red = 255;    //Value from 0(led-off) to 255(). 
uint8_t green = 255; 
uint8_t blue = 0;
int pin = 10;

void decStripSetup() {
  dirStrip.begin(); // Initializes the NeoPixel library
  dirStrip.setBrightness(80); // Value from 0 to 100%
  pinMode(dirStripControlPin, INPUT_PULLUP);
}
void decStripLoop(int loopCounter) {
  int pinState = digitalRead(pin);
  if( pinState == LOW){
    for (int i=0; i<150 ; i++) {
      float v = ((i+loopCounter)%75)/37.50;
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
