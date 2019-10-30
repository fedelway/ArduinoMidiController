#include "NoteProvider.h"

constexpr int step = 7;
constexpr int baseNote = 69;

NoteProvider::NoteProvider(PingSensor& sensor) : sensor(sensor)
{

}

int NoteProvider::getNote()
{
    auto distance = sensor.readDistance();

    if( distance > 20 && distance < 80){
        return baseNote + distance / step;
    }else{
        return -1;
    }
}