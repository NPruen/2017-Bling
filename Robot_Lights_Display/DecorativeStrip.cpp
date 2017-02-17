#include "DecorativeStrip.h"
#include "patCogs.h"
#include "patRotate.h"
#include "patFill.h"
#include "patCylon.h"
#include "patAlternate.h"
#include "patExpandMiddle.h"

#define YELLOW Adafruit_NeoPixel::Color(252, 225, 0)
#define BLUE Adafruit_NeoPixel::Color(20, 85, 251)

#define NUM_PATTERNS 8

static pat *s_patterns[NUM_PATTERNS];

DecorativeStrip::DecorativeStrip(int numLEDs, int stripPin) :
    m_pixels(numLEDs, stripPin, NEO_GRB + NEO_KHZ800),
    m_currentPatternId(0)
{
    int i = 0;
    s_patterns[i++] = new patCogs(m_pixels, YELLOW, BLUE);
    s_patterns[i++] = new patRotate(m_pixels, true, 30);
    s_patterns[i++] = new patRotate(m_pixels, false, 30);
    s_patterns[i++] = new patFill(m_pixels, YELLOW, 10);
    s_patterns[i++] = new patCylon(m_pixels, YELLOW, BLUE, 3);
    s_patterns[i++] = new patAlternate(m_pixels, YELLOW, BLUE, 5);
    s_patterns[i++] = new patFill(m_pixels, YELLOW, 5);
    s_patterns[i++] = new patExpandMiddle(m_pixels, YELLOW, BLUE, 30);
    // if you add more patterns, remember to increase NUM_PATTERNS
}

void DecorativeStrip::setup()
{
  m_pixels.begin(); // Initializes the NeoPixel library
  m_pixels.setBrightness(80); // Value from 0 to 100%
}

void DecorativeStrip::loop(int loopCounter)
{
    pat *currentPattern = s_patterns[m_currentPatternId];
    currentPattern->loop(loopCounter);
    if(currentPattern->done())
    {
        m_currentPatternId = (m_currentPatternId + 1) % NUM_PATTERNS;
        Serial.print("new pattern  ");
        Serial.println(m_currentPatternId);
    }
}
