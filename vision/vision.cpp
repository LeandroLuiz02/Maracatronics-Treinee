#include "vision.h"

Vision::Vision(QString visionAddress, quint16 visionPort) {
    _visionAddress = visionAddress;
    _visionPort = visionPort;
    _visionSocket = new QUdpSocket();

    connectToNetwork();
}

void Vision::connectToNetwork() {
    _visionSocket->bind(QHostAddress(_visionAddress), _visionPort, QUdpSocket::ShareAddress);
    //multicast group (compartilhar recepção de pacotes)
    _visionSocket->joinMulticastGroup(QHostAddress(_visionAddress));
}

void Vision::run() {
    while(_visionSocket->hasPendingDatagrams()) {
        // Receiving datagram
        QNetworkDatagram datagram;
        datagram = _visionSocket->receiveDatagram();

        // Parsing datagram to protobuf
        SSL_WrapperPacket packet;
        packet.ParseFromArray(datagram.data().data(), datagram.data().size());

        // Check if packet has detection
        if(packet.has_detection()) {
            SSL_DetectionFrame visionFrame = packet.detection();

            // Check if frame has balls
            if(visionFrame.balls_size() > 0) {
                // Has ball in frame
                _ball = visionFrame.balls(0);
            }

            // Check if frame has blue robots
            if(visionFrame.robots_blue_size() > 0) {
                for(int i = 0; i < visionFrame.robots_blue_size(); i++) {
                    SSL_DetectionRobot robot = visionFrame.robots_blue(i);
                    _blueRobots.insert(robot.robot_id(), robot);
                }
            }

            // Check if frame has yellow robots
            if(visionFrame.robots_yellow_size() > 0) {
                for(int i = 0; i < visionFrame.robots_yellow_size(); i++) {
                    SSL_DetectionRobot robot = visionFrame.robots_yellow(i);
                    _yellowRobots.insert(robot.robot_id(), robot);
                }
            }
        }

    }
}

SSL_DetectionBall Vision::getBall() {
    return _ball;
}

SSL_DetectionRobot Vision::getRobot(bool isYellow, int id) {
    if(isYellow) {
        if(_yellowRobots.contains(id)) {
            return _yellowRobots.value(id);
        }
        else {
            return SSL_DetectionRobot();
        }
    }
    else {
        if(_blueRobots.contains(id)) {
            return _blueRobots.value(id);
        }
        else {
            return SSL_DetectionRobot();
        }
    }
}
