
#ifndef _EFFECTS_PROVIDER_DEFINED_
#define _EFFECTS_PROVIDER_DEFINED_

#include "pingSensor.h"
#include "MIDI.h"

template<typename MidiImpl>
class EffectsProvider{
public:
    enum class Mode{
        PITCH_BENDING,
        PORTAMENTO_TIME,
        NONE
    };

private:
    MidiImpl& midiImpl;
    PingSensor& ping;
    Mode mode;

public:
    EffectsProvider(MidiImpl& midiImpl, PingSensor& ping);

    void sendEffect();

private:
    void sendPitchBending();
    void sendPortamentoTime();
};

#include "EffectsProvider.hpp"

#endif //_EFFECTS_PROVIDER_DEFINED_