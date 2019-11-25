#include "udpsender.h"

UdpSender::UdpSender(QObject *parent) : QObject(parent)
{

}

void UdpSender::sendVolumeChange(int volume)
{

}
void UdpSender::sendModeChange(QString& mode)
{

}
void UdpSender::setConfiguration(QString& ip, int port)
{
    this->ip = ip;
    this->port = port;

    socket.bind(QHostAddress(ip),port);
}
