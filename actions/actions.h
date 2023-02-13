#ifndef ACTIONS_H
#define ACTIONS_H

#include <QCoreApplication>
#include <vision/vision.h>
#include <actuator/actuator.h>
#include <math.h>
#include <tgmath.h>
#include <chrono>
#include <thread>
#include <time.h>
#include <stdio.h>

float distanceTo(float x, float y, SSL_DetectionRobot robot);
float angleTo(float x, float y, SSL_DetectionRobot robot);
bool angleBetweenOtherTwoAngles(float dynamicAngle, float angle1, float angle2);
bool shouldRotateLeft(float x, float y, SSL_DetectionRobot robot);
void goTo(float x, float y, SSL_DetectionRobot robot, Actuator *actuator,float linearSpeed, float angularSpeed, float isYellow, int id);

class Actions
{
public:
    Actions();
};

#endif // ACTIONS_H
