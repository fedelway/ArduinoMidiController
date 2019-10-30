
#ifndef _PING_SENSOR_DEFINED_
#define _PING_SENSOR_DEFINED_

#include "Arduino.h"

class PingSensor{

    int echoPin;
    int trigPin;

public:
    PingSensor(int echo, int trig);

    int readRawValue();
    int readDistance();
private:
    void fireSensor();
};

#endif
