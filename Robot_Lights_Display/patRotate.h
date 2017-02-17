#include "pat.h"

// patRotate:
//      rotate the existing collection of colors up or down by one
//      pixel.  Pattern is complete after maxCount such moves.

class patRotate : public pat
{
private:
    bool m_up;
    int m_maxCount, m_currentCount;

public:
    patRotate(class Adafruit_NeoPixel &p, bool up, int maxCount):
        pat(p),
        m_up(up),
        m_maxCount(maxCount),
        m_currentCount(0)
    {}

    virtual void loop(int loopCounter)
    {
        CRGB last;
        if(m_up)
        {
            last = m_pixels.getPixelColor(m_pixels.numPixels()-1);
            for(int i=1;i<m_pixels.numPixels();i++)
            {
                m_pixels.setPixelColor(i, m_pixels.getPixelColor(i-1));
            }
            m_pixels.setPixelColor(0, last);
        }
        else
        {
            last = m_pixels.getPixelColor(0);
            for(int i=0;i<m_pixels.numPixels()-1;i++)
            {
                m_pixels.setPixelColor(i, m_pixels.getPixelColor(i+1));
            }
            m_pixels.setPixelColor(m_pixels.numPixels()-1, last);
        }
        m_pixels.show();
        m_currentCount++;
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
