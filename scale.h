#ifndef _SCALE_DEFINED_
#define _SCALE_DEFINED_

class Scale{

    int* distances;
    int length;
    const char* scaleName;

public:
    template<typename T, int size>
    Scale(T (&scale)[size], const char* scaleName): distances(scale), length(size), scaleName(scaleName){ }
    
    int getNote(int step);
    int getLength();
    const char* getName();
};

#endif //_SCALE_DEFINED_