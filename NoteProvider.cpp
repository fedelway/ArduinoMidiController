#include "NoteProvider.h"

constexpr int step = 7;
constexpr int baseNote = 69;
constexpr unsigned long minValue = 1000;
constexpr unsigned long maxValue = 3000;

NoteProvider::NoteProvider(PingSensor& sensor) : sensor(sensor)
{

}

int NoteProvider::getNote()
{
    auto rawValue = sensor.readRawValue();

    if( rawValue > minValue && rawValue < maxValue){
        auto calc = (maxValue - minValue) / step;
        auto actualStep = (rawValue - minValue) / calc;
        return baseNote + scales[1][actualStep];
    }else{
        return -1;
    }
}