#include "wifiClient.h"
#include "Arduino.h" //For Serial Access

WifiClient::WifiClient()
{
}

void WifiClient::setup()
{
    //Init Wifi Connection
    Serial1.begin(115200);
    WiFi.init(&Serial1);
    
    // Check for the presence of the shield
    bool wifiPresent = true;
    if (WiFi.status() == WL_NO_SHIELD) {
        wifiPresent = false;
    }
    
    // attempt to connect to WiFi network
    while ( wifiStatus != WL_CONNECTED && wifiPresent) {
        wifiStatus = WiFi.begin(ssid, pass);

        if(wifiStatus == WL_CONNECTED){
            localIp = WiFi.localIP();
            udpClient.begin(listenPort);
        }
    }
}

IPAddress WifiClient::getIp()
{
    return this->localIp;
}

ProtocolAction WifiClient::receiveInfo()
{
    ProtocolAction retValue;

    if(wifiStatus != WL_CONNECTED){
        retValue.id = 'N';
        return retValue;
    }

    auto length = udpClient.parsePacket();

    if(length != 0){
        this->remoteEndpoint.ip = udpClient.remoteIP();
        this->remoteEndpoint.port = udpClient.remotePort();

        char id = udpClient.read();

        if(id == ProtocolAction::VOLUME_CHANGE){
            char buf[4];
            udpClient.read(buf,3);
            buf[3] = '\0';

            int vol = atoi(buf);
            
            retValue.id = ProtocolAction::VOLUME_CHANGE;
            retValue.changeVolume.volume = vol;
        }
        if(id == ProtocolAction::MODE_CHANGE){
            char mode = udpClient.read();
            
            retValue.id = ProtocolAction::MODE_CHANGE;
            retValue.changeMode.mode = mode;
        }
    }else{
        retValue.id = ProtocolAction::NO_CHANGE;
    }

    return retValue;
}

void WifiClient::sendInfo(char mode, int volume, int note, int scaleNumber)
{
    if(!remoteEndpoint.port)
        return;
  
    char message[10] = {0};

    sprintf(message,"I%c%03.3i%03.3i%1.1i",mode,volume,note,scaleNumber);

    udpClient.beginPacket(remoteEndpoint.ip, remoteEndpoint.port);
    udpClient.write(message,9);
    udpClient.endPacket();
}