#include "Adafruit_NeoPixel.h"

class DirectionalStrip
{
public:
    DirectionalStrip(int numLEDs, int stripPin, int ctlPin);

    void setup();
    void loop(int loopCounter);

private:
    Adafruit_NeoPixel m_pixels;
    int m_ctlPin;
};
