#include "EffectsProvider.h"

template<typename MidiImpl>
EffectsProvider<MidiImpl>::EffectsProvider(MidiImpl& midiImpl, PingSensor& ping)
: midiImpl(midiImpl),
  ping(ping),
  mode(Mode::PITCH_BENDING)
{

}

template<typename MidiImpl>
void EffectsProvider<MidiImpl>::sendEffect()
{
    if(mode == Mode::NONE){
        return;
    }else if(mode == Mode::PITCH_BENDING){
        this->sendPitchBending();
    }else this->sendPortamentoTime();
}

template<typename MidiImpl>
void EffectsProvider<MidiImpl>::sendPitchBending()
{
    int sensorRead = ping.readRawValue();

    if(sensorRead < MIDI_PITCHBEND_MAX){
        this->midiImpl.sendPitchBend(sensorRead,1);
    }
}

template<typename MidiImpl>
void EffectsProvider<MidiImpl>::sendPortamentoTime()
{

}