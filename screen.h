#ifndef _SCREEN_DEFINED_
#define _SCREEN_DEFINED_

#include "LiquidCrystal.h"
#include "IPAddress.h"

class Screen{

LiquidCrystal& lcd;

public:
    Screen(LiquidCrystal& lcd);

    void writeStateChange(const char* stateName);
    void writeVolumeChange(int vol);
    void writeNoteChange(int note);
    void writeScaleChange(const char* scaleName);
    void writeIpAddress(const IPAddress& ip);
};

#endif