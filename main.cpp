#include <iostream>
#include <QCoreApplication>
#include <vision/vision.h>
#include <actuator/actuator.h>
#include <math.h>
#include <chrono>
#include <thread>
#include <time.h>

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
        float angularVelocitys[12] = {0};
        double linearVelocitys[12] = {(0, 0)};
        for (int i = 0; i < 6; i++) {
            robots[i] = vision->getRobot(true, i);
        }
        for (int i = 6; i < 12; i++) {
            robots[i] = vision->getRobot(false, i);
        }


        //debug
        std::cout << robots[0].orientation() << "||" << robots[0].x() << "||" << robots[0].y() << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return a.exec();
}

void SSL_DetectionRobot::rotateToBall(SSL_DetectionBall ball) {
    const float angularAcc = 0.05;
    const float maxAngularVel = 1;

    if(ball.x() > this->x()) {

        if(ball.y() > this->y()) {
            //ballX > robotX || ballY > robotY

        }
    }
}
