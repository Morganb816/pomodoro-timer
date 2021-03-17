#ifndef SCREEN_MANAGER
#define SCREEN_MANAGER

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>

class ScreenManager
{
    public:
        LiquidCrystal *lcd;
        String previousState;
    public:
        ScreenManager(int rs, int en, int d4, int d5, int d6, int d7) {
            lcd = new LiquidCrystal(rs, en, d4, d5, d6, d7);
        }
    public:
        void initialize() {
            lcd->begin(16, 2);
        }
    public:
        void print(String message) {
            if (previousState == message) {
                return;
            }
            previousState = message;
            lcd->clear();
            lcd->print(message);
            lcd->setCursor(0, 0);
        }
};

#endif