
#ifndef _MIDI_CONTROLLER_DEFINED_
#define _MIDI_CONTROLLER_DEFINED_

#include "pingSensor.h"
#include "volumeKnob.h"
#include "MIDI.h"
#include "NoteProvider.h"
#include "VolumeProvider.h"
#include "EffectsProvider.h"
#include "screen.h"

template<typename MidiImpl>
class MidiController{

  int currentNote;
  int currentVolume;
  
  MidiImpl& midiImpl;
  PingSensor ping;
  PingSensor ping2;
  NoteProvider noteProvider;
  VolumeProvider volumeProvider;
  EffectsProvider<MidiImpl> effectsProvider;
  Screen screen;

public:
  MidiController(MidiImpl& midi, PingSensor& ping, PingSensor& ping2, int volPin, LiquidCrystal& lcd);

  void setup();
  void loop();

  void cancelPreviousNote();
  void cancelNote(int note);

  void changeMode(char mode);
  
  MidiImpl& getMidiImpl();
};

#include "controller.hpp"

#endif //_MIDI_CONTROLLER_DEFINED_
