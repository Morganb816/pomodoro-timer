#ifndef SONG_EVENT
#define SONG_EVENT

#include <Arduino.h>
#include <Event.hpp>
#include <Song.hpp>

class SongEvent : public Event
{
    Song song;

public:
    SongEvent(Song _song)
    {
        song = _song;
    }

public:
    void run()
    {
        Serial.println("PLAYING SONG");
        song.playSong();
    }
};

#endif