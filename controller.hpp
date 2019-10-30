#include "controller.h"

constexpr int step = 7;

template<typename MidiImpl>
MidiController<MidiImpl>::MidiController(MidiImpl& midiImpl,PingSensor& ping,PingSensor& ping2, int volPin) 
  : midiImpl(midiImpl),
  ping(ping),
  ping2(ping2),
  volumeKnob(volPin)
{
  this->currentNote = 0;
}

template<typename MidiImpl>
void MidiController<MidiImpl>::setup(){
}

template<typename MidiImpl>
void MidiController<MidiImpl>::loop(){
    int distance = this->ping.readDistance();

    this->sendDistanceNote(distance);
}

template<typename MidiImpl>
void MidiController<MidiImpl>::cancelPreviousNote(){
  this->cancelNote(currentNote);
}

template<typename MidiImpl>
void MidiController<MidiImpl>::cancelNote(int note){
  if(note != 0){
    this->midiImpl.sendNoteOff(note,127,1);
  }
}

template<typename MidiImpl>
void MidiController<MidiImpl>::sendDistanceNote(int distance){
  if( distance > 20 && distance < 80){
    int newNote = 69 + distance / step;

    if(currentNote != newNote){
      int previousNote = currentNote;
      currentNote = newNote;
      this->midiImpl.sendNoteOn(currentNote, volumeKnob.readVolume(), 1);
      this->cancelNote(previousNote);
    }else{

    }

    this->sendPitchBend(); 
  }else{
    this->cancelPreviousNote();
    //To prevent sending constant noteoff messages
    currentNote = 0;
  }
}

template<typename MidiImpl>
void MidiController<MidiImpl>::sendPitchBend(){
  int sensorRead = ping2.readRawValue();

  if(sensorRead < MIDI_PITCHBEND_MAX){
    this->midiImpl.sendPitchBend(sensorRead,1);
  }
}

template<typename MidiImpl>
MidiImpl& MidiController<MidiImpl>::getMidiImpl(){
  return this->midiImpl;
}