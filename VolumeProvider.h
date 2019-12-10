
#ifndef _VOLUME_PROVIDER_DEFINED_
#define _VOLUME_PROVIDER_DEFINED_

#include "pingSensor.h"

template<typename MidiImpl>
class VolumeProvider{
    
public:
    enum class Mode{
        CONSTANT,
        MODULATED
    };

private:
    uint8_t potPin;
    Mode mode;
    PingSensor& ping;
    MidiImpl& midiImpl;
    int currentVolume;

public:

    VolumeProvider(uint8_t potPin, PingSensor& ping, MidiImpl& midiImpl);

    int readVolume();
    void sendAfterTouch();
    void changeMode(Mode mode);
};

#include "VolumeProvider.hpp"

#endif //_VOLUME_PROVIDER_DEFINED_