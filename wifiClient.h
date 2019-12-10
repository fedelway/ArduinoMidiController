#ifndef _WIFI_DATA_CLIENT_DEFINED_
#define _WIFI_DATA_CLIENT_DEFINED_

//#include "WiFiEspAT.h"
#include "WiFiEsp.h"
#include "WiFiEspUdp.h"
#include "LiquidCrystal.h"

struct UdpEndPoint{
    IPAddress ip;
    int port;
};

union ProtocolAction{

    static constexpr char VOLUME_CHANGE = 'V';
    static constexpr char MODE_CHANGE = 'M';
    static constexpr char NO_CHANGE = 'N';

    char id;
    struct {
        char id;
        char mode;
    } changeMode;
    struct{
        char id;
        int volume;
    } changeVolume;
};

class WifiClient{

    static constexpr int listenPort = 8081;
    static constexpr const char* ssid = "ssid";
    static constexpr const char* pass = "password";
    static constexpr int MAX_CONNECTION_ATTEMPTS = 5;

    UdpEndPoint remoteEndpoint;
    WiFiEspUDP udpClient;
    IPAddress localIp;
    LiquidCrystal& lcd;
    int wifiStatus = WL_IDLE_STATUS;
    unsigned long lastSentTime;
    unsigned long lastReceivedTime;
    bool received;
    bool connected;

public:
    WifiClient(LiquidCrystal& lcd);
    void setup();

    IPAddress& getIp();

    ProtocolAction receiveInfo();
    void sendInfo(char mode, int volume, int note, int scaleNumber);
};

#endif //_WIFI_DATA_CLIENT_DEFINED_