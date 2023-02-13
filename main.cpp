#include <iostream>
#include <QCoreApplication>
#include <vision/vision.h>
#include <actuator/actuator.h>
#include <actions/actions.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Vision *vision = new Vision("224.5.23.2", 10020);
    Actuator *actuator = new Actuator("127.0.0.1", 20011);

    while(true) {
        //detect ball and robots
        vision->run();

        SSL_DetectionBall ball = vision->getBall();
        SSL_DetectionRobot robots[12]; //first 6 robots are yellow
        //float angularVelocitys[12] = {0};
        for (int i = 0; i < 6; i++) {
            robots[i] = vision->getRobot(true, i);
        }
        for (int i = 6; i < 12; i++) {
            robots[i] = vision->getRobot(false, i);
        }

        goTo(0, 0, robots[0], actuator, 1, 2, true, 0);
        //actuator->sendCommand(true, 0, 0, 0, 5);

        //DEBUG
        std::cout << shouldRotateLeft(ball.x(), ball.y(), robots[0]) << std::endl;
        //std::cout << robots[0].orientation()<< std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return a.exec();
}
