#ifndef _WIFI_DATA_CLIENT_DEFINED_
#define _WIFI_DATA_CLIENT_DEFINED_

#include "WiFiEsp.h"
#include "WiFiEspUdp.h"

struct UdpEndPoint{
    IPAddress ip;
    int port;
}

union ProtocolAction{
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

    constexpr int listenPort = 8081;
    constexpr char ssid[] = "DisiLabHotSpot";
    constexpr char pass[] = "AccessAir";

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