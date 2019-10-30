
#ifndef _VOLUME_KNOB_DEFINED_
#define _VOLUME_KNOB_DEFINED_

#include "Arduino.h"

class VolumeKnob{
    int pin;

public:
    inline VolumeKnob(int pin) : pin(pin) {}

    inline int readVolume(){
        return analogRead(pin) / 9;
    }
};

#endif //_VOLUME_KNOB_DEFINED_