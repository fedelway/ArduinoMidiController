#include "scale.h"

Scale::Scale(int* distances, int length) : distances(distances), length(length)
{

}

int Scale::getNote(int step)
{
    return distances[step % length];
}