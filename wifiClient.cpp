#include "wifiClient.h"
#include "Arduino.h" //For Serial Access

WifiClient::WifiClient(LiquidCrystal& lcd) : lcd(lcd), lastSentTime(0), lastReceivedTime(0), connected(false)
{
    this->remoteEndpoint.port = 0;
}

void WifiClient::setup()
{    
    //Init Wifi Connection
    lcd.home();
    lcd.print("INICIANDO WIFI");
    Serial1.begin(115200);
    WiFi.init(&Serial1);
    
    // Check for the presence of the shield
    bool wifiPresent = true;
    if (WiFi.status() == WL_NO_SHIELD) {
        lcd.home();
        lcd.print("WIFI NO PRESENTE");
        wifiPresent = false;
    }
    
    // attempt to connect to WiFi network
    int attempts = 0;
    lcd.home();
    lcd.print("CONECTANDO WIFI:");
    lcd.setCursor(0,1);
    while ( wifiStatus != WL_CONNECTED && wifiPresent) {
        lcd.print(".");

        attempts++;

        if(attempts > MAX_CONNECTION_ATTEMPTS){
            lcd.home();
            lcd.print("                ");
            lcd.home();
            lcd.print("NO SE PUDO");
            lcd.setCursor(0,1);
            lcd.print("CONECTAR");
            connected = false;
            delay(1000);
            break;
        }

        wifiStatus = WiFi.begin(ssid, pass);

        if(wifiStatus == WL_CONNECTED){
            localIp = WiFi.localIP();
            udpClient.begin(listenPort);

            lcd.home();
            lcd.print("                ");
            lcd.home();
            lcd.print("CONEXION EXITOSA");
            connected = true;
            delay(1000);
        }
    }
}

IPAddress& WifiClient::getIp()
{
    return this->localIp;
}

ProtocolAction WifiClient::receiveInfo()
{
    ProtocolAction retValue;

    if(!connected){
        retValue.id = 'N';
        return retValue;
    }

    auto now = millis();
    
    if( (now - this->lastReceivedTime) < 100 && !received)
        return;
    this->lastReceivedTime = now;

    auto start = millis();
    auto length = udpClient.parsePacket();
    auto end = millis();
    
    Serial.print("Parse packet tomo: ");
    Serial.print(end-start);
    Serial.print("Length: ");
    Serial.println(length);

    if(length != 0){
        received = true;
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
        received = false;
    }

    return retValue;
}

void WifiClient::sendInfo(char mode, int volume, int note, int scaleNumber)
{
    if(!connected){
        return;
    }
    if(!remoteEndpoint.port)
        return;
    
    auto now = millis();
    if( (now - this->lastSentTime) < 100 )
        return;

    this->lastSentTime = now;

    char message[10] = {0};

    Serial.println("Llegue a armar mensaje");

    sprintf(message,"I%c%03.3i%03.3i%1.1i",mode,volume,note,scaleNumber);

    Serial.println(message);

    udpClient.beginPacket(remoteEndpoint.ip, remoteEndpoint.port);
    udpClient.write(message,9);
    udpClient.endPacket();
}