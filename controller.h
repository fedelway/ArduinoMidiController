
#ifndef _MIDI_CONTROLLER_DEFINED_
#define _MIDI_CONTROLLER_DEFINED_

#include "pingSensor.h"
#include "volumeKnob.h"
#include "MIDI.h"
#include "NoteProvider.h"
#include "VolumeProvider.h"
#include "EffectsProvider.h"

template<typename MidiImpl>
class MidiController{

  int currentNote;
  MidiImpl& midiImpl;
  PingSensor ping;
  PingSensor ping2;
  NoteProvider noteProvider;
  VolumeProvider volumeProvider;
  EffectsProvider<MidiImpl> effectsProvider;

public:
  MidiController(MidiImpl& midi, PingSensor& ping, PingSensor& ping2, int volPin);

  void setup();
  void loop();

  void cancelPreviousNote();
  void cancelNote(int note);

  MidiImpl& getMidiImpl();
};

#include "controller.hpp"

#endif //_MIDI_CONTROLLER_DEFINED_
