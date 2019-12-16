#include "NoteProvider.h"
#include "Arduino.h"

constexpr int step = 7;
constexpr unsigned long minValue = 1000;
constexpr unsigned long maxValue = 3000;
constexpr unsigned long noValueRange = 150;

NoteProvider::NoteProvider(PingSensor& sensor) : sensor(sensor), scaleNumber(0), configuredScale(scales[5]), baseNote(57)
{

}

int NoteProvider::getNote()
{
    auto rawValue = sensor.readRawValue();

    if( rawValue > minValue && rawValue < maxValue){
        auto calc = (maxValue - minValue) / configuredScale.getLength();
        auto actualStep = (rawValue - minValue) / calc;

        if( actualStep != 0 )
        {
            unsigned long threshold = calc * actualStep;
            unsigned long adjustedRawValue = rawValue - minValue;
            
            /*
            Serial.print("Raw: ");
            Serial.print(adjustedRawValue);
            Serial.print("threshold: ");
            Serial.println(threshold);*/

            if(adjustedRawValue < (threshold + (noValueRange/2)) && adjustedRawValue > (threshold - (noValueRange/2)) ){
                //Serial.println("Callo en el rango");
                return -2;
            }
            //checkeo limite superior
            threshold = calc * (actualStep+1);
            if(adjustedRawValue < (threshold + (noValueRange/2)) && adjustedRawValue > (threshold - (noValueRange/2)) ){
                //Serial.println("Callo en el rango");
                return -2;
            }
        }

        return baseNote + configuredScale.getNote(actualStep);
    }else{
        return -1;
    }
}

void NoteProvider::setScale(int number)
{
    if(number < (scaleCount-1)){
        configuredScale = scales[number];
        scaleNumber = number;
    }
}

Scale& NoteProvider::getScale()
{
    return configuredScale;
}

void NoteProvider::incrementBaseNote()
{
    if(baseNote < 127)
        baseNote++;
}

void NoteProvider::decrementBaseNote()
{
    if(baseNote > 0)
        baseNote--;
}

void NoteProvider::incrementOctave()
{
    if(baseNote + 12 < 127)
        baseNote += 12;
}

void NoteProvider::decrementOctave()
{
    if(baseNote - 12 > 0)
        baseNote -= 12;
}