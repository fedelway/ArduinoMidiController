
#ifndef _NOTE_PROVIDER_DEFINED_
#define _NOTE_PROVIDER_DEFINED_

#include "pingSensor.h"

class NoteProvider {

    PingSensor& sensor;
    int scales[3][12] = {
        {1,2,3,4,5,6,7,8 ,9 ,10,11,12},     //Cromatic
        {2,4,5,7,9,11,12,-1,-1,-1,-1,-1},   //Mayor scale
        {2,3,5,7,8,10,12,-1 ,-1,-1,-1,-1}   //Minor scale
    };

public:
    NoteProvider(PingSensor& sensor);
    int getNote();
};

#endif //_NOTE_PROVIDER_DEFINED_