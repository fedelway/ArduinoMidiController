#ifndef _SCALE_DEFINED_
#define _SCALE_DEFINED_

class Scale{

    int* distances;
    int length;

public:
    template<typename T, int size>
    Scale(T (&scale)[size]): distances(scale), length(size){ }
    
    int getNote(int step);
    int getLength();
};

#endif //_SCALE_DEFINED_