
#ifndef _CONTROLLER_MODE_DEFINED_
#define _CONTROLLER_MODE_DEFINED_

#include "controller.h"
#include "MIDI.h"
#include "Arduino.h"

class ControllerMode{
    MidiController<midi::MidiInterface<HardwareSerial>>& controller;

public:
    ControllerMode(MidiController<midi::MidiInterface<HardwareSerial>>& controller);

    void loop();
};

#endif //_CONTROLLER_MODE_DEFINED_