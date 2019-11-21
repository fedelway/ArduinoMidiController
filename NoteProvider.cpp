#include "NoteProvider.h"

constexpr int step = 7;
constexpr int baseNote = 69;
constexpr unsigned long minValue = 1000;
constexpr unsigned long maxValue = 3000;

/*Scale NoteProvider::scales[] = {
    Scale(NamedScales::cromatic, "Cromatic"),
    Scale(NamedScales::major, "Major"),
    Scale(NamedScales::minor, "Minor"),
    Scale(NamedScales::armonicMinor, "Arm.Minor"),
    Scale(NamedScales::melodicMinor, "Mel.Minor"),
};*/

NoteProvider::NoteProvider(PingSensor& sensor) : sensor(sensor), configuredScale(scales[0])
{

}

int NoteProvider::getNote()
{
    auto rawValue = sensor.readRawValue();

    if( rawValue > minValue && rawValue < maxValue){
        auto calc = (maxValue - minValue) / configuredScale.getLength();
        auto actualStep = (rawValue - minValue) / calc;

        return baseNote + configuredScale.getNote(actualStep);
    }else{
        return -1;
    }
}

void NoteProvider::setScale(int number)
{
    if(number < scaleCount)
        configuredScale = scales[number];
}

Scale& NoteProvider::getScale()
{
    return configuredScale;
}