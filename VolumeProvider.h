
#ifndef _VOLUME_PROVIDER_DEFINED_
#define _VOLUME_PROVIDER_DEFINED_

#include "pingSensor.h"

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

public:

    VolumeProvider(uint8_t potPin, PingSensor& ping);

    int readVolume();
};

#endif //_VOLUME_PROVIDER_DEFINED_