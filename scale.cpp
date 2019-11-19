#include "scale.h"

int Scale::getNote(int step)
{
    return distances[step % length];
}

int Scale::getLength()
{
    return length;
}