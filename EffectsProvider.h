
#ifndef _EFFECTS_PROVIDER_DEFINED_
#define _EFFECTS_PROVIDER_DEFINED_

#include "pingSensor.h"
#include "MIDI.h"

template<typename MidiImpl>
class EffectsProvider{
public:
    enum class Mode{
        PITCH_BENDING,
        PITCH_BENDING_POT,
        CC_104,     //Sends CC 104 messages
        CC_105,     //Sends CC 105 messages
        NONE
    };

private:
    MidiImpl& midiImpl;
    PingSensor& ping;
    Mode mode;
    uint8_t potPin;

public:
    EffectsProvider(MidiImpl& midiImpl, PingSensor& ping, uint8_t potPin);

    void sendEffect();
    void changeMode(Mode newMode);

private:
    void sendPitchBending();
    void sendPotPitchBending();
};

#include "EffectsProvider.hpp"

#endif //_EFFECTS_PROVIDER_DEFINED_