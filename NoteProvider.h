
#ifndef _NOTE_PROVIDER_DEFINED_
#define _NOTE_PROVIDER_DEFINED_

#include "pingSensor.h"
#include "namedScales.h"
#include "scale.h"

class NoteProvider {

    PingSensor& sensor;
    Scale& configuredScale;

    static constexpr int scaleCount = 6;
    Scale scales[scaleCount] = {
        Scale(NamedScales::cromatic, "Cromatic"),
        Scale(NamedScales::major, "Major"),
        Scale(NamedScales::minor, "Minor"),
        Scale(NamedScales::armonicMinor, "Arm.Minor"),
        Scale(NamedScales::melodicMinor, "Mel.Minor"),
        Scale(NamedScales::cromatic, "Cromatic")
    };

public:
    int scaleNumber;

    NoteProvider(PingSensor& sensor);
    int getNote();
    void setScale(int scaleNumber);
    Scale& getScale();
};

#endif //_NOTE_PROVIDER_DEFINED_
