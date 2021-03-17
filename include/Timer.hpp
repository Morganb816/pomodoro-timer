#ifndef TIMER
#define TIMER

#include <Arduino.h>
#include <Event.hpp>

class Timer
{
public:
    long startTime;
    long timerLengthInMilliseconds;
    bool running = false;
    Event *eventOnCompletion;
    Event *eventOnStart;

public:
    Timer(long _timerLengthInMilliseconds, Event *_eventOnStart, Event *_eventOnCompletion = nullptr)
    {
        timerLengthInMilliseconds = _timerLengthInMilliseconds;
        eventOnCompletion = _eventOnCompletion;
        eventOnStart = _eventOnStart;
    }

public:
    Timer()
    {
        ;
    }

public:
    void startTimer()
    {
        startTime = millis();
        eventOnStart->run();
        running = true;
    }

public:
    void stopTimer()
    {
        running = false;
    }

public:
    bool isTimerComplete()
    {
        if (!running)
        {
            return false;
        }
        long timeEllapsed = millis() - startTime;
        if (timeEllapsed >= timerLengthInMilliseconds)
        {
            if (eventOnCompletion)
            {
                eventOnCompletion->run();
            }
            return true;
        }
        return false;
    }
public:
    int secondsLeft() {
        if (!running) {
            return 0;
        }
        return (timerLengthInMilliseconds - (millis() - startTime)) / 1000;
    }
};

#endif