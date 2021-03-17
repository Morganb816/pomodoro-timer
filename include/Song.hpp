#ifndef SONG
#define SONG

#include <Arduino.h>

class Song
{
public:
    int *song;
    int songLength;
    int buzzerPin;

public:
    Song()
    {
        ;
    }

public:
    Song(int _song[], int _songLength, int _buzzerPin)
    {
        song = _song;
        songLength = _songLength;
        buzzerPin = _buzzerPin;
    }

public:
    void playSong()
    {
        for (int i = 0; i < songLength; i++)
        {
            tone(buzzerPin, song[i]);
            delay(250);
        }
        noTone(buzzerPin);
    }
};

#endif