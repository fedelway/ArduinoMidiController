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
  ping2, 
  ping,
  potPin,
  lcd);

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen to all incoming messages
  Serial.begin(115200); //Cambiamos la velocidad del puerto serie
  lcd.begin(16,2);

  //testComponents();

  keypad.addEventListener(keypadEvent); //add an event listener for this keypad

  controller.setup();
}

void loop() {
  //To trigger listeners
  char key = keypad.getKey();

  controller.loop();
}

void keypadEvent(KeypadEvent key){
  switch (keypad.getState()){
    case PRESSED:
      controller.changeMode(key);
      break;
  }
}

void testComponents()
{
  lcd.home();
  lcd.print("test left ping");
  while(true){
    auto value = ping.readParametrizedValue(10);
    if(value != -1)
      break;
  }

  lcd.home();
  lcd.print("test right ping");
  while(true){
    auto value = ping2.readParametrizedValue(10);
    if(value != -1)
      break;
  }

  lcd.home();
  lcd.print("               ");
  lcd.home();
  lcd.print("test knob");
  {
    auto initialValue = analogRead(potPin);
    while(true){
      auto newValue = analogRead(potPin);

      auto diff = newValue > initialValue ? newValue - initialValue : initialValue - newValue;
      if( diff > 10 )
        break;
    }
  }

  lcd.home();
  lcd.print("test keypad");
  lcd.setCursor(0,1);
  lcd.print("Press: ");
  
  auto offset = strlen("Press: ");
  testAndPrint('1',offset);
  testAndPrint('5',offset);
  testAndPrint('9',offset);
  testAndPrint('D',offset);

  lcd.clear();
  lcd.print("TEST OK");
  lcd.setCursor(0,1);
  lcd.print("Press A to end");
  testKey('A');
  lcd.clear();
}

void testAndPrint(char key, int offset)
{
  lcd.setCursor(offset, 1);
  lcd.print(key);
  testKey(key);
}

void testKey(char key)
{
  while(true){
    auto pressedKey = keypad.getKey();
    if(pressedKey == key)
      break;
  }
}