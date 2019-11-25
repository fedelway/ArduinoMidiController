#include "udpsender.h"
#include <QNetworkDatagram>
#include "scalenames.h"

UdpSender::UdpSender(QObject *parent) : QObject(parent)
{
    connect(&socket,&QUdpSocket::readyRead,this,&UdpSender::processIncomingData);
}

bool UdpSender::isValid()
{
    return socket.isValid();
}

void UdpSender::setConfiguration(const QString& ip, int port)
{
    qDebug() << "IP: " << ip << " port: " << port;

    this->controllerAddress = QHostAddress(ip);
    this->controllerPort = port;

    socket.close();
    socket.bind(controllerAddress,controllerPort);

    configurationFinished(socket.isValid());
}

void UdpSender::sendVolumeChange(int volume)
{
    qDebug() << "Send volume change: " << volume;
    char buffer[4];

    buffer[0] = 'V';
    auto numberString = QString::number(volume).rightJustified(3,'0',true);
    memcpy(buffer + 1,numberString.toLatin1().data(),numberString.length());

    qDebug() << "Message made: " << QString::fromStdString(std::string(buffer,sizeof(buffer)));

    socket.writeDatagram(buffer,sizeof(buffer),controllerAddress,controllerPort);
}

void UdpSender::sendModeChange(const QString& mode)
{
    qDebug() << "Send mode change: " << mode;

    char buffer[2];

    buffer[0] = 'M';
    buffer[1] = mode.toLatin1().data()[0];

    qDebug() << "Message made: " << QString::fromStdString(std::string(buffer,sizeof(buffer)));

    socket.writeDatagram(buffer,sizeof(buffer),controllerAddress,controllerPort);
}


void UdpSender::processIncomingData()
{
    const size_t dataLength = 9;
    auto datagram = socket.receiveDatagram();

    auto data = datagram.data();
    auto rawData = data.data();

    if(data[0] != 'I' || data.length() != dataLength)
        return;

    QString mode(rawData[1]);

    char volBuf[4] = {0};
    memcpy(volBuf,rawData+2,3);
    int volume = atoi(volBuf);

    char noteBuf[4] = {0};
    memcpy(noteBuf,rawData+5,3);
    int note = atoi(noteBuf);

    QString scaleName;
    size_t scale = (rawData[8] - '0');
    if(scale < ScaleNames::names.size())
        scaleName = ScaleNames::names[scale];
    else scaleName = "";

    dataChange(mode,volume,note,scaleName);
}
