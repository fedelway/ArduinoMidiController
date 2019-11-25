#ifndef UDPSENDER_H
#define UDPSENDER_H

#include <QObject>
#include <QUdpSocket>

class UdpSender : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool valid READ isValid)

    QUdpSocket socket;
    quint16 controllerPort;
    QHostAddress controllerAddress;


public:
    explicit UdpSender(QObject *parent = nullptr);
    bool isValid();

signals:
    void configurationFinished(bool valid);

public slots:
    void sendVolumeChange(int volume);
    void sendModeChange(const QString& mode);
    void setConfiguration(const QString& ip, int port);
};

#endif // UDPSENDER_H
