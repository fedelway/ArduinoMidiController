#ifndef UDPSENDER_H
#define UDPSENDER_H

#include <QObject>
#include <QUdpSocket>

class UdpSender : public QObject
{
    Q_OBJECT

    QUdpSocket socket;
    QString ip;
    int port;

public:
    explicit UdpSender(QObject *parent = nullptr);

signals:
    void configurationFinished(bool isValid);

public slots:
    void sendVolumeChange(int volume);
    void sendModeChange(QString& mode);
    void setConfiguration(const QString& ip, int port);
};

#endif // UDPSENDER_H
