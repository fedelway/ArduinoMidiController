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
        //Serial.println("WiFi not present");
        wifiPresent = false;
        lcd.home();
        lcd.print("NO WIFI");
    }
    
    // attempt to connect to WiFi network
    while ( wifiStatus != WL_CONNECTED && wifiPresent) {
        wifiStatus = WiFi.begin(ssid, pass);

        if(wifiStatus == WL_CONNECTED){
            localIp = WiFi.localIP();
            udp.begin(listenPort);
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
    auto length = udpClient.parsePacket();

    if(length != 0){
        this->remoteEndpoint.ip = udpClient.remoteIP();
        this->remoteEndpoint.port = udpClient.remotePort();

        char id = udpClient.read();

        if(id == 'V'){
            char buf[4];
            udp.read(buf,3);
            buf[3] = '\0';

            int vol = atoi(buf);
            
            retValue.id = 'V';
            retValue.changeVolume.volume = vol;
        }
        if(id == 'M'){
            char mode = udpClient.read();
            
            retValue.id = 'M';
            retValue.changeMode.mode = 'M';
        }
    }else{
        retValue.id = 'N';
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