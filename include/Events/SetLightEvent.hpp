#ifndef SET_WORK_LIGHT
#define SET_WORK_LIGHT

#include <Arduino.h>
#include <RGBLed.hpp>
#include <Event.hpp>

class SetLightEvent : public Event
{
    RGBLed *rgbLed;
    int r;
    int g;
    int b;

public:
    SetLightEvent(RGBLed *_rgbLed, int _r, int _g, int _b)
    {
        rgbLed = _rgbLed;
        r = _r;
        g = _g;
        b = _b;
    }

public:
    void run()
    {
        rgbLed->assignColor(r, g, b);
    }
};

#endif