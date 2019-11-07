
#ifndef _PING_SENSOR_DEFINED_
#define _PING_SENSOR_DEFINED_

#include "Arduino.h"

class PingSensor{
    static constexpr int numberOfReadings = 15;
    static constexpr unsigned long maxValue = 999999;

    uint8_t echoPin;
    uint8_t trigPin;
    unsigned long previousReadings[15] = {maxValue};
    uint8_t currentReading;

public:
    PingSensor(int echo, int trig);

    unsigned long readRawValue();
    unsigned long readStabilizedValue();
    int readDistance();
private:
    void fireSensor();
    void saveValue(int value);
};

#endif
