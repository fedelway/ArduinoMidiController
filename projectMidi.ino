#include "WiFiEsp.h"
#include "WiFiEspUdp.h"
#include "controller.h"
#include <MIDI.h>
#include "Keypad.h"
#include "LiquidCrystal.h"

#ifdef _ESPLOGLEVEL_
#undef _ESPLOGLEVEL_
#endif

#define _ESPLOGLEVEL_ 0

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

// Create WIFI instance
char ssid[] = "DisiLabHotSpot";   // your network SSID (name)
char pass[] = "AccessAir";        // your network password
// A UDP instance to let us send and receive packets over UDP
WiFiEspUDP udp;
int wifiStatus = WL_IDLE_STATUS;     // the Wifi radio's status
int localPort = 8081;

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
  lcd,
  udp);

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);  // Listen to all incoming messages
  Serial.begin(115200); //Cambiamos la velocidad del puerto serie
  keypad.addEventListener(keypadEvent); //add an event listener for this keypad
  lcd.begin(16,2);

/*
  // initialize serial for ESP module
  Serial1.begin(115200);
  WiFi.init(&Serial1);
  
  // check for the presence of the shield
  bool wifiPresent = true;
  if (WiFi.status() == WL_NO_SHIELD) {
    //Serial.println("WiFi not present");
    wifiPresent = false;
    lcd.home();
    lcd.print("NO WIFI");
  }
  
  // attempt to connect to WiFi network
  while ( wifiStatus != WL_CONNECTED && wifiPresent) {
    //Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    wifiStatus = WiFi.begin(ssid, pass);

    if(wifiStatus == WL_CONNECTED){
      // you're connected now, so print out the data
      //Serial.println("You're connected to the network");
      
      udp.begin(localPort);

      IPAddress ip = WiFi.localIP();
      Serial.println(ip);
      lcd.home();
      lcd.print(ip);
    }
  }

  //delay(5000);
*/

  controller.setup();
}

void loop() {
  //To trigger listeners
  char key = keypad.getKey();
  
  /*auto value = ping2.readStabilizedValue();
  Serial.println(value);*/

  controller.loop();
}

void keypadEvent(KeypadEvent key){
  switch (keypad.getState()){
    case PRESSED:
      //Serial.println(key);
      controller.changeMode(key);
      break;
  }
}
