#ifndef ACTUATOR_H
#define ACTUATOR_H

#include <QUdpSocket>
#include <protobufs/grSim_Packet.pb.h>

class Actuator
{
public:
    Actuator(QString actuatorAddress, quint16 actuatorPort);
    void sendCommand(bool isYellow, int id, float vx, float vy, float vw);

private:
    QUdpSocket *_actuatorSocket;
    QString _actuatorAddress;
    quint16 _actuatorPort;

    void connectToNetwork();
};

#endif // ACTUATOR_H
