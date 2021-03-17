#ifndef PIN_HANDLER
#define PIN_HANDLER

#include <Arduino.h>

class PinHandler
{
public:
    int pinNumber;
    boolean isInput;
    int pinState;

public:
    PinHandler(int _pinNumber)
    {
        pinNumber = _pinNumber;
        pinState = LOW;
        pinMode(pinNumber, true);
    }

public:
    void checkState()
    {
        int newState = digitalRead(pinNumber);
        if (pinState != newState)
        {
            pinState = newState;
            if (newState == HIGH)
            {
                handleStateChange(newState);
            }
        }
    }

public:
    virtual void handleStateChange(int newState) = 0;
};

#endif