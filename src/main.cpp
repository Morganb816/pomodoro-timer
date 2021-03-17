#include <Arduino.h>
#include <Timer.hpp>
#include <TimerManager.hpp>
#include <PinHandler.hpp>
#include <Handlers/StartStopHandler.hpp>
#include <Song.hpp>
#include <RGBLed.hpp>
#include <Event.hpp>
#include <Events/SetLightEvent.hpp>
#include <Handlers/ProgressHandler.hpp>
#include <Events/SongEvent.hpp>
#include <Events/EventGroup.hpp>
#include <ScreenManager.hpp>

long longBreakTime = 60000 * 15;
long shortBreakTime = 60000 * 5;
long workTime = 60000 * 25;

int START_STOP_BUTTON_PIN = 2;
int PROGRESS_BUTTON_PIN = 7;
int BUZZER_PIN = 8;

int buzzerSong[] = {250, 500, 750, 1500, 750, 1000};
int songLength = 6;
Song alarmDoneSong(buzzerSong, songLength, BUZZER_PIN);
SongEvent alarmDoneSongEvent(alarmDoneSong);

RGBLed rgbLed(4, 5, 6, 0, 0, 0);
SetLightEvent setWorkLight(&rgbLed, 100, 10, 10);
SetLightEvent setShortBreakLight(&rgbLed, 10, 100, 10);
SetLightEvent setLongBreakLight(&rgbLed, 10, 10, 100);

Event *workEvents[] = {&setWorkLight, &alarmDoneSongEvent};
EventGroup workEventGroup(workEvents, 2);
Event *shortBreakEvents[] = {&setShortBreakLight, &alarmDoneSongEvent};
EventGroup shortBreakEventGroup(shortBreakEvents, 2);
Event *longBreakEvents[] = {&setLongBreakLight, &alarmDoneSongEvent};
EventGroup longBreakEventGroup(longBreakEvents, 2);

Timer longBreakTimer(longBreakTime, &longBreakEventGroup);
Timer breakTimer(shortBreakTime, &shortBreakEventGroup);
Timer workTimer(workTime, &workEventGroup);

Timer timerArray[] = {workTimer, breakTimer, workTimer, breakTimer, workTimer, longBreakTimer};
int timerArrayLength = 6;

TimerManager mainTimerManager(timerArray, timerArrayLength);
StartStopHandler startStopHandler(START_STOP_BUTTON_PIN, &mainTimerManager);
ProgressHandler progressHandler(PROGRESS_BUTTON_PIN, &mainTimerManager);

ScreenManager screenManager(52, 53, 51, 49, 47, 45);

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
    ;
  }
  rgbLed.turnOn();
  screenManager.initialize();
}

void loop()
{
  mainTimerManager.checkTimers();
  startStopHandler.checkState();  
  int secondsLeft = mainTimerManager.currentTimeLeft();
  int minutesLeft = 0;
  int hoursLeft = 0;
  while (secondsLeft >= 60) {
    minutesLeft += 1;
    secondsLeft -= 60;
  };
  String secondsLeftString = String(secondsLeft);
  String minutesLeftString = String(minutesLeft);
  String timeLeft = minutesLeftString + ':' + secondsLeftString;
  screenManager.print(timeLeft);
  progressHandler.checkState();
  Serial.println(String(mainTimerManager.currentTimeLeft()));
}