
#ifndef _NOTE_PROVIDER_DEFINED_
#define _NOTE_PROVIDER_DEFINED_

#include "pingSensor.h"
#include "namedScales.h"
#include "scale.h"

class NoteProvider {

    PingSensor& sensor;
    Scale& configuredScale;

    static constexpr int scaleCount = 5;

public:
    static Scale scales[scaleCount];

    NoteProvider(PingSensor& sensor);
    int getNote();
    void setScale(int scaleNumber);
    Scale& getScale();
};

#endif //_NOTE_PROVIDER_DEFINED_
