#include "scale.h"

int Scale::getNote(int step)
{
    return distances[step % length];
}

int Scale::getLength()
{
    return this->length;
}

const char* Scale::getName()
{
    return this->scaleName;
}