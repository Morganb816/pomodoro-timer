#ifndef RGB_LED
#define RGB_LED

#include <Arduino.h>

class RGBLed
{
public:
    bool isOn;
    int *colorCode;
    int rPin;
    int gPin;
    int bPin;

public:
    RGBLed()
    {
        ;
    }

public:
    RGBLed(int _rPin, int _gPin, int _bPin, int r, int g, int b)
    {
        isOn = false;
        rPin = _rPin;
        gPin = _gPin;
        bPin = _bPin;
        pinMode(rPin, OUTPUT);
        pinMode(gPin, OUTPUT);
        pinMode(gPin, OUTPUT);
        assignColor(r, g, b);
    }

public:
    void writePins(int r, int g, int b)
    {
        analogWrite(rPin, r);
        analogWrite(gPin, g);
        analogWrite(bPin, b);
    }

public:
    void turnOn()
    {
        isOn = true;
        writePins(colorCode[0], colorCode[1], colorCode[2]);
    }

public:
    void turnOff()
    {
        isOn = false;
        writePins(0, 0, 0);
    }

public:
    void assignColor(int r, int g, int b)
    {
        int rColor = r;
        int gColor = g;
        int bColor = b;
        int colorCodeArray[] = {rColor, gColor, bColor};
        colorCode = colorCodeArray;
        if (isOn == true)
        {
            turnOn();
        }
    }
};

#endif