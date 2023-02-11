#ifndef VISION_H
#define VISION_H

#include <QUdpSocket>
#include <QNetworkDatagram>
#include <protobufs/ssl_vision_wrapper.pb.h>

class Vision
{
public:
    Vision(QString visionAddress, quint16 port);
    void run();

    SSL_DetectionBall getBall();
    SSL_DetectionRobot getRobot(bool isYellow, int id);

private:
    QUdpSocket *_visionSocket;
    QString _visionAddress;
    quint16 _visionPort;

    void connectToNetwork();

    SSL_DetectionBall _ball;
    QMap<int, SSL_DetectionRobot> _blueRobots;
    QMap<int, SSL_DetectionRobot> _yellowRobots;

};

#endif // VISION_H
