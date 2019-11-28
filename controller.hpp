#include "controller.h"

constexpr int step = 7;

template<typename MidiImpl>
MidiController<MidiImpl>::MidiController(MidiImpl& midiImpl,PingSensor& ping,PingSensor& ping2, int volPin, LiquidCrystal& lcd, WiFiEspUDP& udp) 
  : midiImpl(midiImpl),
  ping(ping),
  ping2(ping2),
  noteProvider(ping),
  volumeProvider(volPin, ping2),
  effectsProvider(midiImpl, ping2),
  screen(lcd),
  udp(udp)
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

  this->receiveInfo();

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

  if(newVolume != currentVolume && newVolume % 2 == 0){
    screen.writeVolumeChange(newVolume);
    currentVolume = newVolume;
  }
  
  this->sendInfo();
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
    this->volumeProvider.changeMode(VolumeProvider::Mode::CONSTANT);
    this->screen.writeStateChange("PBEND");
  }
  if(mode == 'B'){
    this->effectsProvider.changeMode(EffectsProvider<MidiImpl>::Mode::NONE);
    this->volumeProvider.changeMode(VolumeProvider::Mode::MODULATED);
    this->screen.writeStateChange("VOLMOD");
  }
  if(mode == 'D'){
    this->effectsProvider.changeMode(EffectsProvider<MidiImpl>::Mode::PORTAMENTO_TIME);
    this->volumeProvider.changeMode(VolumeProvider::Mode::CONSTANT);
    this->screen.writeStateChange("PTIME");
  }

  if(isdigit(mode)){
    this->noteProvider.setScale(mode - '0');
    this->screen.writeScaleChange(this->noteProvider.getScale().getName());
  }

  this->mode = mode;
}

template<typename MidiImpl>
void MidiController<MidiImpl>::receiveInfo(){
  auto length = udp.parsePacket();

  if(length != 0){
    this->remoteIp = udp.remoteIP();
    this->remotePort = udp.remotePort();

    char id = udp.read();

    if(id == 'V'){
      char buf[4];
      udp.read(buf,3);
      buf[3] = '\0';

      int vol = atoi(buf);
      //Send vol to controller
    }
    if(id == 'M'){
      char mode = udp.read();

      this->changeMode(mode);
    }
  }

}

template<typename MidiImpl>
void MidiController<MidiImpl>::sendInfo()
{
  if(!remotePort)
    return;
  
  char message[10] = {0};

  sprintf(message,"I%c%03.3i%03.3i%1.1i",mode,currentVolume,currentNote,noteProvider.scaleNumber);

  //Serial.println(message);

  udp.beginPacket(remoteIp, remotePort);

  udp.write(message,9);

  udp.endPacket();
}