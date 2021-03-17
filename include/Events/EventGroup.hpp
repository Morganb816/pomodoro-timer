#ifndef EVENT_GROUP
#define EVENT_GROUP

#include <Arduino.h>
#include <Event.hpp>

class EventGroup : public Event
{
public:
    Event **events;
    int amountOfEvents;

public:
    EventGroup(Event *_events[], int _amountOfEvents)
    {
        events = _events;
        amountOfEvents = _amountOfEvents;
    }

public:
    void run()
    {
        for (int i = 0; i < amountOfEvents; i++)
        {
            events[i]->run();
        }
    }
};

#endif