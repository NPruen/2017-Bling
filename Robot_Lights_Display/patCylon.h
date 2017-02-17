#include "pat.h"

// patCylon:
//    Writes two pixels per interation.  c1 moves accross the background
//    and c2 fills in where it left behind.
//
//    Inspired by Battlestart Galactica villians.

class patCylon : public pat
{
private:
    CRGB m_c1, m_c2;
    int m_maxCount, m_currentCount;

public:
    patCylon(class Adafruit_NeoPixel &p, CRGB c1, CRGB c2, int maxCount):
        pat(p),
        m_c1(c1),
        m_c2(c2),
        m_maxCount(maxCount),
        m_currentCount(0)
    {}

    virtual void loop(int loopCounter)
    {
        int nleds = m_pixels.numPixels();
        int lastled = nleds - 1;
        int i = loopCounter % nleds;
        if(m_currentCount % 1 == 0)
        {
            // on even cycles we move upward
            m_pixels.setPixelColor(i, m_c1);
            if(i!=0)
                m_pixels.setPixelColor(i-1, m_c2);
        }
        else
        {
            // on odd cycles we go the other way
            i = nleds - i;
            m_pixels.setPixelColor(i, m_c1);
            if(i!=lastled)
                m_pixels.setPixelColor(i+1, m_c2);
        }
        m_pixels.show();
        if(i == lastled)
            m_currentCount++; // one cycle complete
    }

    virtual bool done()
    {
        if(m_currentCount < m_maxCount)
            return false;
        else
        {
            m_currentCount = 0;
            return true;
        }
    }
};
