
#ifndef _NOTE_PROVIDER_DEFINED_
#define _NOTE_PROVIDER_DEFINED_

#include "pingSensor.h"

class NoteProvider {

    PingSensor& sensor;

public:
    NoteProvider(PingSensor& sensor);
    int getNote();
};

#endif //_NOTE_PROVIDER_DEFINED_