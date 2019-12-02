
#ifndef _PING_SENSOR_DEFINED_
#define _PING_SENSOR_DEFINED_

#include "Arduino.h"

class PingSensor{
    static constexpr int numberOfReadings = 4;
    static constexpr unsigned long maxValue = 999999;
    static constexpr int sensorTimeOut = 4000;

    uint8_t echoPin;
    uint8_t trigPin;
    unsigned long previousReadings[numberOfReadings] = {maxValue};
    uint8_t currentReading;

public:
    PingSensor(int echo, int trig);

    unsigned long readRawValue();
    unsigned long readStabilizedValue();
    int readParametrizedValue(int range);
    int readDistance();
private:
    void fireSensor();
    void saveValue(unsigned long value);
};

#endif
