#include "controller.h"

constexpr int step = 7;

template<typename MidiImpl>
MidiController<MidiImpl>::MidiController(MidiImpl& midiImpl,PingSensor& ping,PingSensor& ping2, int volPin) 
  : midiImpl(midiImpl),
  ping(ping),
  ping2(ping2),
  noteProvider(ping),
  volumeProvider(volPin, ping2),
  effectsProvider(midiImpl, ping2)
{
  this->currentNote = 0;
}

template<typename MidiImpl>
void MidiController<MidiImpl>::setup(){
}

template<typename MidiImpl>
void MidiController<MidiImpl>::loop(){
  auto newNote = this->noteProvider.getNote();

  if(newNote != -1){
    this->midiImpl.sendNoteOn(newNote, volumeProvider.readVolume(), 1);
    this->cancelNote(currentNote);
    currentNote = newNote;

    this->effectsProvider.sendEffect();
  }else{
    this->cancelPreviousNote();
    currentNote = 0;
  }

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
MidiImpl& MidiController<MidiImpl>::getMidiImpl(){
  return this->midiImpl;
}