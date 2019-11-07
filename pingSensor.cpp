#include "pingSensor.h"

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
    auto value = pulseIn(echoPin, HIGH);
    this->saveValue(value);
    return value;
}

unsigned long PingSensor::readStabilizedValue()
{
    this->readRawValue();

    int acum = 0;
    int i = 0;
    for(i = 0; i<numberOfReadings && previousReadings[i] != maxValue; i++){
        acum += previousReadings[i];
    }

    return acum / i;
}

int PingSensor::readDistance()
{
    return this->readStabilizedValue() / 29 / 2;
}

void PingSensor::saveValue(int value)
{
    this->previousReadings[this->currentReading] = value;
    this->currentReading = (currentReading + 1) % numberOfReadings;
}