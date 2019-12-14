#include "controller.h"
#include "Arduino.h"

template<typename MidiImpl>
MidiController<MidiImpl>::MidiController(MidiImpl& midiImpl,PingSensor& ping,PingSensor& ping2, int volPin, LiquidCrystal& lcd) 
  : midiImpl(midiImpl),
  ping(ping),
  ping2(ping2),
  noteProvider(ping),
  volumeProvider(volPin, ping2, midiImpl),
  effectsProvider(midiImpl, ping2, volPin),
  screen(lcd),
  wifiClient(lcd)
{
  this->currentNote = 0;
  this->currentVolume = 0;
  this->cancelCount = 0;
}

template<typename MidiImpl>
void MidiController<MidiImpl>::setup(){
  wifiClient.setup();
  screen.writeStateChange("PBEND");
}

template<typename MidiImpl>
void MidiController<MidiImpl>::loop(){

  this->receiveInfo();

  auto newNote = this->noteProvider.getNote();
  auto newVolume = volumeProvider.readVolume();

  if(newNote != -1){
    cancelCount = 0;
    if(newNote != currentNote && newNote != -2){
      this->midiImpl.sendNoteOn(newNote,newVolume, 1);
      delay(25);
      this->cancelNote(currentNote);
      currentNote = newNote;
      this->screen.writeNoteChange(newNote);
    }

    //Send After-touch (dynamic volume change)
    this->volumeProvider.sendAfterTouch();
  }else{
    cancelCount++;

    if(cancelCount >= CANCEL_NOTE_COUNT_REQUIRED){
      this->cancelPreviousNote();
      currentNote = 0;
      cancelCount = 0;
    }
  }

  this->effectsProvider.sendEffect();

  if(newVolume != currentVolume && newVolume % 2 == 0){
    screen.writeVolumeChange(newVolume);
    currentVolume = newVolume;
  }
  
  wifiClient.sendInfo(this->mode,this->currentVolume,this->currentNote,noteProvider.scaleNumber);
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
    this->volumeProvider.changeMode(VolumeProvider<MidiImpl>::Mode::CONSTANT);
    this->screen.writeStateChange("PBEND");
  }
  if(mode == 'B'){
    this->effectsProvider.changeMode(EffectsProvider<MidiImpl>::Mode::PITCH_BENDING_POT);
    this->volumeProvider.changeMode(VolumeProvider<MidiImpl>::Mode::MODULATED);
    this->screen.writeStateChange("VOLMOD");
  }
  if(mode == '*'){
    this->screen.writeIpAddress(this->wifiClient.getIp());
  }

  if(isdigit(mode)){
    this->noteProvider.setScale(mode - '0');
    this->screen.writeScaleChange(this->noteProvider.getScale().getName());
  }

  this->mode = mode;
}

template<typename MidiImpl>
void MidiController<MidiImpl>::receiveInfo()
{
    auto info = wifiClient.receiveInfo();

    if(info.id == ProtocolAction::NO_CHANGE)
      return;
    if(info.id == ProtocolAction::MODE_CHANGE){
      this->changeMode(info.changeMode.mode);
    }
    if(info.id == ProtocolAction::VOLUME_CHANGE){
      this->volumeProvider.applyAppVolume(info.changeVolume.volume);
      //this->currentVolume = info.changeVolume.volume;
    }
}