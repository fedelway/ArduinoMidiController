#include "EffectsProvider.h"
#include "Arduino.h"

template<typename MidiImpl>
EffectsProvider<MidiImpl>::EffectsProvider(MidiImpl& midiImpl, PingSensor& ping, uint8_t potPin)
: midiImpl(midiImpl),
  ping(ping),
  mode(Mode::PITCH_BENDING),
  potPin(potPin)
{

}

template<typename MidiImpl>
void EffectsProvider<MidiImpl>::changeMode(Mode newMode)
{
    this->mode = newMode;
}

template<typename MidiImpl>
void EffectsProvider<MidiImpl>::sendEffect()
{
    if(mode == Mode::NONE){
        return;
    }else if(mode == Mode::PITCH_BENDING){
        this->sendPitchBending();
    }else if(mode == Mode::PITCH_BENDING_POT){
        this->sendPotPitchBending();
    }
    else if(mode == Mode::CC_104){
        auto sensorRead = ping.readParametrizedValue(127);

        if(sensorRead != -1)
            this->midiImpl.sendControlChange(104,sensorRead,1);
    }else if(mode == Mode::CC_105){
        auto sensorRead = ping.readParametrizedValue(127);

        if(sensorRead != -1)
            this->midiImpl.sendControlChange(105,sensorRead,1);
    }
}

template<typename MidiImpl>
void EffectsProvider<MidiImpl>::sendPitchBending()
{
    long sensorRead = ping.readParametrizedValue(MIDI_PITCHBEND_MAX * 2);
    static long previousSensorRead = -1;

    if(sensorRead == -1 && previousSensorRead == -1)
        return;

    if(sensorRead != -1){
        previousSensorRead = sensorRead;
        this->midiImpl.sendPitchBend( (int)(sensorRead - MIDI_PITCHBEND_MAX), 1 );
    }else{
        previousSensorRead = -1;
        this->midiImpl.sendPitchBend(0, 1);
    }
}

template<typename MidiImpl>
void EffectsProvider<MidiImpl>::sendPotPitchBending()
{
    auto read = analogRead(potPin);
    int value = map(read,0,1023,0,MIDI_PITCHBEND_MAX * 2) - MIDI_PITCHBEND_MAX;

    this->midiImpl.sendPitchBend(value, 1);
}