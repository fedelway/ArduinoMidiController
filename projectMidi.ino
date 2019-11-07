#include "controller.h"
#include <MIDI.h>
#include "Keypad.h"
#include "LiquidCrystal.h"

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {52, 53, 50, 51}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {47, 46, 45, 44}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Created and binds the MIDI interface to the default hardware Serial port
MIDI_CREATE_DEFAULT_INSTANCE();

LiquidCrystal lcd(3, 2, 9, 10, 11, 12);

//Create Ping Sensors
constexpr int echo1 = A1;
constexpr int trig1 = 36;
PingSensor ping(echo1,trig1);

constexpr int echo2 = A3;
constexpr int trig2 = 23;
PingSensor ping2(echo2,trig2);

constexpr int potPin = A5;

//Create midiController class
MidiController<midi::MidiInterface<HardwareSerial>> controller(
  MIDI, 
  ping, 
  ping2,
  potPin);

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen to all incoming messages
  Serial.begin(115200); //Cambiamos la velocidad del puerto serie
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
  lcd.begin(16,2);
  lcd.print("Hello World");
}

void loop() {
  //To trigger listeners
  //char key = keypad.getKey();
  
  //Serial.println(analogRead(A5));
  Serial.println(ping2.readStabilizedValue());

  //controller.loop();
}

void keypadEvent(KeypadEvent key){
  switch (keypad.getState()){
    case PRESSED:
      //Serial.println(key);
      if( isalpha(key)){
        controller.changeMode(key);
      }
      break;
  }
}