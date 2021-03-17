#ifndef START_STOP_HANDLER
#define START_STOP_HANDLER

#include <Arduino.h>
#include <TimerManager.hpp>
#include <PinHandler.hpp>

class StartStopHandler : public PinHandler
{
public:
    boolean isRunning;
    TimerManager *timerManager;

public:
    StartStopHandler(int _pinNumber, TimerManager *_timerManager) : PinHandler(_pinNumber)
    {
        isRunning = false;
        timerManager = _timerManager;
    }

public:
    void handleStateChange(int newState)
    {
        if (newState == HIGH)
        {
            isRunning = !isRunning;
        }
        if (isRunning)
        {
            timerManager->startTimers();
            return;
        }
        timerManager->stopTimers();
    }
};

#endif