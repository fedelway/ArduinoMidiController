#include "EffectsProvider.h"
#include "Arduino.h"

template<typename MidiImpl>
EffectsProvider<MidiImpl>::EffectsProvider(MidiImpl& midiImpl, PingSensor& ping)
: midiImpl(midiImpl),
  ping(ping),
  mode(Mode::PITCH_BENDING)
{

}

template<typename MidiImpl>
void EffectsProvider<MidiImpl>::changeMode(Mode newMode)
{
    this->mode = newMode;

    //Activate/Deactivate portamento time
    if(mode == Mode::PORTAMENTO_TIME){
        this->midiImpl.sendControlChange(65,127,1);
    }
    else this->midiImpl.sendControlChange(65,0,1);
}

template<typename MidiImpl>
void EffectsProvider<MidiImpl>::sendEffect()
{
    if(mode == Mode::NONE){
        return;
    }else if(mode == Mode::PITCH_BENDING){
        this->sendPitchBending();
    }else if(mode == Mode::PORTAMENTO_TIME){
        this->sendPortamentoTime();
    }
}

template<typename MidiImpl>
void EffectsProvider<MidiImpl>::sendPitchBending()
{
    long sensorRead = ping.readParametrizedValue(MIDI_PITCHBEND_MAX * 2);

    this->midiImpl.sendPitchBend( (int)(sensorRead - MIDI_PITCHBEND_MAX), 1 );
}

template<typename MidiImpl>
void EffectsProvider<MidiImpl>::sendPortamentoTime()
{
    int sensorRead = ping.readDistance();

    this->midiImpl.sendControlChange(5,sensorRead,1);
}