
#ifndef _VOLUME_PROVIDER_DEFINED_
#define _VOLUME_PROVIDER_DEFINED_

#include "pingSensor.h"

template<typename MidiImpl>
class VolumeProvider{
    
public:
    enum class Mode{
        CONSTANT,
        MODULATED,
        APP
    };

private:
    uint8_t potPin;
    Mode mode;
    PingSensor& ping;
    MidiImpl& midiImpl;
    int currentVolume;
    int analogVolume;
    Mode previousMode;

public:

    VolumeProvider(uint8_t potPin, PingSensor& ping, MidiImpl& midiImpl);

    int readVolume();
    void sendAfterTouch();
    void changeMode(Mode mode);
    void applyAppVolume(int newVol);
};

#include "VolumeProvider.hpp"

#endif //_VOLUME_PROVIDER_DEFINED_