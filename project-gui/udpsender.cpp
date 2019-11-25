#include "udpsender.h"

UdpSender::UdpSender(QObject *parent) : QObject(parent)
{

}

void UdpSender::setConfiguration(const QString& ip, int port)
{
    this->ip = ip;
    this->port = port;

    qDebug() << "IP: " << ip << " port: " << port;

    socket.close();
    socket.bind(QHostAddress(ip),port);

    configurationFinished(socket.isValid());
}

void UdpSender::sendVolumeChange(int volume)
{
    qDebug() << "Send volume change: " << volume;
}

void UdpSender::sendModeChange(const QString& mode)
{
    qDebug() << "Send mode change: " << mode;
}
