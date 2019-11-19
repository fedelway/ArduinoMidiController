#include "controller.h"

constexpr int step = 7;

template<typename MidiImpl>
MidiController<MidiImpl>::MidiController(MidiImpl& midiImpl,PingSensor& ping,PingSensor& ping2, int volPin, LiquidCrystal& lcd) 
  : midiImpl(midiImpl),
  ping(ping),
  ping2(ping2),
  noteProvider(ping),
  volumeProvider(volPin, ping2),
  effectsProvider(midiImpl, ping2),
  screen(lcd)
{
  this->currentNote = 0;
  this->currentVolume = 0;
}

template<typename MidiImpl>
void MidiController<MidiImpl>::setup(){
  screen.writeStateChange("PBEND");
}

template<typename MidiImpl>
void MidiController<MidiImpl>::loop(){
  auto newNote = this->noteProvider.getNote();
  auto newVolume = volumeProvider.readVolume();

  if(newNote != -1){

    if(newNote != currentNote){
      this->midiImpl.sendNoteOn(newNote,newVolume, 1);
      this->cancelNote(currentNote);
      currentNote = newNote;
      this->screen.writeNoteChange(newNote);
    }

    //Send After-touch (dynamic volume change)
    //this->volumeProvider.sendAfterTouch();

    this->effectsProvider.sendEffect();

  }else{
    this->cancelPreviousNote();
    currentNote = 0;
  }

  if(newVolume != currentVolume){
    screen.writeVolumeChange(newVolume);
    currentVolume = newVolume;
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

template<typename MidiImpl>
void MidiController<MidiImpl>::changeMode(char mode){
  if(mode == 'A'){
    this->effectsProvider.changeMode(EffectsProvider<MidiImpl>::Mode::PITCH_BENDING);
    this->screen.writeStateChange("PBEND");
  }
  if(mode == 'D'){
    this->effectsProvider.changeMode(EffectsProvider<MidiImpl>::Mode::PORTAMENTO_TIME);
    this->screen.writeStateChange("PTIME");
  }

  if(isdigit(mode)){
    this->noteProvider.setScale(mode - '0');
  }
}