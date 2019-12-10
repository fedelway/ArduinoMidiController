
#ifndef _MIDI_CONTROLLER_DEFINED_
#define _MIDI_CONTROLLER_DEFINED_

#include "pingSensor.h"
#include "volumeKnob.h"
#include "MIDI.h"
#include "NoteProvider.h"
#include "VolumeProvider.h"
#include "EffectsProvider.h"
#include "screen.h"
#include "wifiClient.h"

template<typename MidiImpl>
class MidiController{

  static constexpr int CANCEL_NOTE_COUNT_REQUIRED = 20;

  int cancelCount;
  int currentNote;
  int currentVolume;

  IPAddress remoteIp;
  int remotePort;
  char mode = 'A';

  MidiImpl& midiImpl;
  PingSensor ping;
  PingSensor ping2;
  NoteProvider noteProvider;
  VolumeProvider<MidiImpl> volumeProvider;
  EffectsProvider<MidiImpl> effectsProvider;
  Screen screen;
  WifiClient wifiClient;

public:
  MidiController(MidiImpl& midi, PingSensor& ping, PingSensor& ping2, int volPin, LiquidCrystal& lcd);

  void setup();
  void loop();

  void cancelPreviousNote();
  void cancelNote(int note);

  void changeMode(char mode);

  void receiveInfo();
  
  MidiImpl& getMidiImpl();
};

#include "controller.hpp"

#endif //_MIDI_CONTROLLER_DEFINED_
