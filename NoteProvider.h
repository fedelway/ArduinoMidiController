
#ifndef _NOTE_PROVIDER_DEFINED_
#define _NOTE_PROVIDER_DEFINED_

#include "pingSensor.h"
#include "namedScales.h"
#include "scale.h"

class NoteProvider {

    PingSensor& sensor;
    Scale& configuredScale;

    static constexpr int scaleCount = 5;
    Scale scales[scaleCount] = {
        Scale(NamedScales::cromatic),
        Scale(NamedScales::major),
        Scale(NamedScales::minor),
        Scale(NamedScales::armonicMinor),
        Scale(NamedScales::melodicMinor),
    };

public:
    NoteProvider(PingSensor& sensor);
    int getNote();
    void setScale(int scaleNumber);
};

#endif //_NOTE_PROVIDER_DEFINED_
