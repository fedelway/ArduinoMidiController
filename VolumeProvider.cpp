#include "VolumeProvider.h"
#include "Arduino.h"

VolumeProvider::VolumeProvider(uint8_t potPin, PingSensor& ping) 
: potPin(potPin), 
  mode(Mode::CONSTANT),
  ping(ping)
{

}

int VolumeProvider::readVolume()
{
    return analogRead(potPin) / 9;
}