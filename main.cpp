#include <iostream>
#include <QCoreApplication>
#include <vision/vision.h>
#include <actuator/actuator.h>
#include <math.h>
#include <tgmath.h>
#include <chrono>
#include <thread>
#include <time.h>
#include <stdio.h>

//FUNCTION DECLARATION
float distanceToBall(SSL_DetectionBall ball, SSL_DetectionRobot robot);
float angleToBall(SSL_DetectionBall ball, SSL_DetectionRobot robot);

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

        actuator->sendCommand(true, 0, 0, 0, 0.3);

        //DEBUG
        std::cout << angleToBall(ball, robots[0])<< std::endl;
        //std::cout << robots[0].orientation()<< std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    return a.exec();
}

/*FUNCTION DEFINITION
-----------------------------------------------------------------------*/
float distanceToBall(SSL_DetectionBall ball, SSL_DetectionRobot robot) {

    // returned value = sqrt( (b.x - r.x)² + (b.y - r.y)² ), that is the module of a vector
    return sqrt(pow(ball.x() - robot.x(), 2) + pow(ball.y() - robot.y(), 2));

}

float angleToBall(SSL_DetectionBall ball, SSL_DetectionRobot robot) {

    //in case the ball has a lower y than the robot, the angle returned should have a negative value
    int signal = 1;
    if (ball.y() < robot.y()) signal = -1;

    // uses the formula that returns the angle between two vectors
    return signal * acos(((ball.x() - robot.x())) / (distanceToBall(ball, robot)));
}
