 #include "actuator.h"

Actuator::Actuator(QString actuatorAddress, quint16 actuatorPort) {
    _actuatorAddress = actuatorAddress;
    _actuatorPort = actuatorPort;
    _actuatorSocket = new QUdpSocket();

    connectToNetwork();
}

void Actuator::connectToNetwork() {
    if(_actuatorSocket->isOpen()) {
        _actuatorSocket->close();
    }
    // protocolo ipv4 é usado na competição
    _actuatorSocket->connectToHost(_actuatorAddress, _actuatorPort, QIODevice::WriteOnly, QAbstractSocket::IPv4Protocol);
}

void Actuator::sendCommand(bool isYellow, int id, float vx, float vy, float vw) {
    // Create grSimPacket
    grSim_Packet packet;

    // Set macro informations
    packet.mutable_commands()->set_isteamyellow(isYellow);
    packet.mutable_commands()->set_timestamp(0.0); // serve apenas para debug da competição

    // Create robot command message
    grSim_Robot_Command *command = packet.mutable_commands()->add_robot_commands();

    // Setting commands
    // Set robot id
    command->set_id(id);

    // Set velocity
    command->set_wheelsspeed(false); // não queremos utilizar as velocidades das rodas
    command->set_veltangent(vx);
    command->set_velnormal(vy);
    command->set_velangular(vw);

    // Set kick speed
    command->set_kickspeedx(0.0);
    command->set_kickspeedz(0.0);

    // Set spinner
    command->set_spinner(false);

    // Send data to simulator
    std::string buffer;
    packet.SerializeToString(&buffer);

    // Write buffer in network
    _actuatorSocket->write(buffer.c_str(), buffer.length());
}
