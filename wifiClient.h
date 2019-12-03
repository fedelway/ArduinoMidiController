#ifndef _WIFI_DATA_CLIENT_DEFINED_
#define _WIFI_DATA_CLIENT_DEFINED_

#include "WiFiEsp.h"
#include "WiFiEspUdp.h"

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
    static constexpr const char* ssid = "DisiLabHotSpot";
    static constexpr const char* pass = "AccessAir";

    UdpEndPoint remoteEndpoint;
    WiFiEspUDP udpClient;
    IPAddress localIp;
    int wifiStatus = WL_IDLE_STATUS;

public:
    WifiClient();
    void setup();

    IPAddress getIp();

    ProtocolAction receiveInfo();
    void sendInfo(char mode, int volume, int note, int scaleNumber);
};

#endif //_WIFI_DATA_CLIENT_DEFINED_