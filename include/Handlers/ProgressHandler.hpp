#ifndef PROGRESS_HANDLER
#define PROGRESS_HANDLER

#include <Arduino.h>
#include <PinHandler.hpp>
#include <TimerManager.hpp>

class ProgressHandler : public PinHandler
{
public:
    TimerManager *timerManager;

public:
    ProgressHandler(int _pinNumber, TimerManager *_timerManager) : PinHandler(_pinNumber)
    {
        timerManager = _timerManager;
    }

public:
    void handleStateChange(int newState)
    {
        timerManager->finishAndProgress();
    }
};

#endif