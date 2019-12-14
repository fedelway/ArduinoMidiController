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
        analogVolume = currentVolume;
    }
    else if(mode == Mode::MODULATED){
        auto vol = ping.readParametrizedValue(127);
        
        if(vol != -1)
            currentVolume = vol;
        analogVolume = currentVolume;
    }
    // If mode is set to APP check if the volume changed to see if mode should change back to selected mode
    else if(mode == Mode::APP){
        if(previousMode == Mode::CONSTANT){
            auto read = analogRead(potPin);
            auto newVol = map(read,0,1023,0,127);
            if(newVol > (analogVolume+2) || newVol < (analogVolume-2) ){
                this->mode = Mode::CONSTANT;
                currentVolume = newVol;
                analogVolume = newVol;
            }
        }
        if(previousMode == Mode::MODULATED){
            auto newVol = ping.readParametrizedValue(127);

            if(newVol != -1){
                currentVolume = newVol;
                analogVolume = currentVolume;
                mode == Mode::MODULATED;
            }
        }
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

template<typename MidiImpl>
void VolumeProvider<MidiImpl>::applyAppVolume(int newVol)
{
    this->currentVolume = newVol;
    if(this->mode != Mode::APP)
        this->previousMode = this->mode;
    this->mode = Mode::APP;
}