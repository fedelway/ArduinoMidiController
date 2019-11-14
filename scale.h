#ifndef _SCALE_DEFINED_
#define _SCALE_DEFINED_

class Scale{

int* distances;
int length;

public:
    Scale(int* distances, int length);
    
    int getNote(int step);
};

#endif //_SCALE_DEFINED_