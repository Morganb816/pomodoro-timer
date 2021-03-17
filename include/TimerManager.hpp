#ifndef TIMER_MANAGER
#define TIMER_MANAGER

#include <Arduino.h>
#include <Timer.hpp>

class TimerManager
{
public:
    Timer *timers;
    int amountOfTimers;
    int currentTimer = 0;
    bool timersRunning = false;

public:
    TimerManager(Timer _timers[], int _amountOfTimers)
    {
        timers = _timers;
        amountOfTimers = _amountOfTimers;
    }

public:
    TimerManager()
    {
        ;
    }

public:
    void startTimers()
    {
        timersRunning = true;
        Serial.println(timersRunning);
        timers[currentTimer].startTimer();
    }

public:
    void stopTimers()
    {
        timersRunning = false;
        timers[currentTimer].stopTimer();
        currentTimer = 0;
    }

private:
    void moveToNextTimer()
    {
        if (currentTimer + 1 == amountOfTimers)
        {
            currentTimer = 0;
            return;
        }
        currentTimer++;
    }

public:
    void handleTimerFinished()
    {
        timers[currentTimer].stopTimer();
        moveToNextTimer();
        timers[currentTimer].startTimer();
    }

public:
    void finishAndProgress()
    {
        if (timers[currentTimer].eventOnCompletion)
        {
            timers[currentTimer].eventOnCompletion->run();
        }
        handleTimerFinished();
    }

public:
    void checkTimers()
    {
        if (!timersRunning)
        {
            return;
        }
        if (timers[currentTimer].isTimerComplete())
        {
            handleTimerFinished();
        }
    }

public:
    int currentTimeLeft()
    {
        return timers[currentTimer].secondsLeft();
    }
};

#endif