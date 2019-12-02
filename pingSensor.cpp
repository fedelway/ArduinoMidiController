#include "pingSensor.h"
#include "Arduino.h"

PingSensor::PingSensor(int echo, int trig) : echoPin(echo), trigPin(trig), currentReading(0)
{
    pinMode(this->trigPin, OUTPUT);
    pinMode(this->echoPin, INPUT);
}

void PingSensor::fireSensor()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
}

unsigned long PingSensor::readRawValue()
{
    this->fireSensor();
    //Return duration
    auto value = pulseIn(echoPin, HIGH, sensorTimeOut);
    this->saveValue(value);
    return value;
}

unsigned long PingSensor::readStabilizedValue()
{
    this->readRawValue();

    unsigned long acum = 0;
    unsigned long i = 0;
    for(i = 0; i<numberOfReadings; i++){
        acum += previousReadings[i];
    }

    return acum / numberOfReadings;
}

int PingSensor::readDistance()
{
    return this->readStabilizedValue() / 29 / 2;
}

int PingSensor::readParametrizedValue(int range)
{
    constexpr unsigned long maxValue = 3000;
    constexpr unsigned long minValue = 1000;

    auto rawValue = this->readRawValue();
    if( rawValue > minValue && rawValue < maxValue){
        return map(rawValue,minValue,maxValue,0,range);
    }else{
        return -1;
    }
}

void PingSensor::saveValue(unsigned long value)
{
    this->previousReadings[this->currentReading] = value;
    this->currentReading = (currentReading + 1) % numberOfReadings;
}