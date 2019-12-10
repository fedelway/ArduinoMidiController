#include "VolumeProvider.h"
#include "Arduino.h"

template<typename MidiImpl>
VolumeProvider<MidiImpl>::VolumeProvider(uint8_t potPin, PingSensor& ping, MidiImpl& midiImpl) 
: potPin(potPin), 
  mode(Mode::CONSTANT),
  ping(ping),
  midiImpl(midiImpl),
  currentVolume(0)
{

}

template<typename MidiImpl>
int VolumeProvider<MidiImpl>::readVolume()
{
    if(mode == Mode::CONSTANT){
        auto read = analogRead(potPin);
        currentVolume = map(read,0,1023,0,127);
    }
    else if(mode == Mode::MODULATED){
        auto vol = ping.readParametrizedValue(127);
        
        if(vol != -1)
            currentVolume = vol;
    }

    return currentVolume;
}

template<typename MidiImpl>
void VolumeProvider<MidiImpl>::changeMode(Mode mode)
{
    this->mode = mode;
}

template<typename MidiImpl>
void VolumeProvider<MidiImpl>::sendAfterTouch()
{
    if(mode != Mode::MODULATED)
        return;

    auto volumeRead = readVolume();

    if(volumeRead != -1)
        this->midiImpl.sendAfterTouch(readVolume(), 1);
}