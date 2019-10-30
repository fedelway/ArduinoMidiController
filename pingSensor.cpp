#include "pingSensor.h"

PingSensor::PingSensor(int echo, int trig) : echoPin(echo), trigPin(trig)
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

int PingSensor::readRawValue()
{
    this->fireSensor();
    //Return duration
    return pulseIn(echoPin, HIGH);
}

int PingSensor::readDistance()
{
    return this->readRawValue() / 29 / 2;
}
