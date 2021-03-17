#ifndef EVENT
#define EVENT

#include <Arduino.h>
class Event
{
public:
    virtual void run()
    {
        Serial.print("test");
    };
};

#endif