#include "actions.h"

Actions::Actions()
{

}

float distanceTo(float x, float y, SSL_DetectionRobot robot) {

    // returned value = sqrt( (x - r.x)² + (y - r.y)² ), that is the module of a vector
    return sqrt(pow(x - robot.x(), 2) + pow(y - robot.y(), 2));

}

float angleTo(float x, float y, SSL_DetectionRobot robot) {

    //in case the ball has a lower y than the robot, the angle returned should have a negative value
    int signal = 1;
    if (y < robot.y()) signal = -1;

    // uses the formula that returns the angle between two vectors
    return signal * acos(((x - robot.x())) / (distanceTo(x, y, robot)));
}

bool angleBetweenOtherTwoAngles(float dynamicAngle, float angle1, float angle2) {
    //verify if a given angle is between other two angles
    if ((dynamicAngle < angle1 && dynamicAngle > angle2) || (dynamicAngle > angle1 && dynamicAngle < angle2))
        return true;
    else return false;
}

// not working properly yet
bool shouldRotateLeft(float x, float y, SSL_DetectionRobot robot) {
    float toBallOrientation = angleTo(x, y, robot);

    // in case both robot orientation and ball orientation has same signal
    if (toBallOrientation * robot.orientation() > 0) {

        if (toBallOrientation > robot.orientation()) return true;
        else return false;
    }

    else {
        if (toBallOrientation > 0) { // using sqrt(pow()) to get absolute value
            if (toBallOrientation + sqrt(pow(robot.orientation(), 3)) < M_PI)
                return true;
            else return false;
        }
        else if (toBallOrientation + sqrt(pow(robot.orientation(), 3)) > M_PI)
            return false;
        else return true;
    }
}

void goTo(float x, float y, SSL_DetectionRobot robot, Actuator *actuator,float linearSpeed, float angularSpeed, float isYellow, int id) {
    float relativeOrientation = angleTo(x, y, robot) - robot.orientation();
    float vx = cos(relativeOrientation) * linearSpeed;
    float vy = sin(relativeOrientation) * linearSpeed;
    float vw = angularSpeed;
    if (!shouldRotateLeft(x, y, robot)) vw = -angularSpeed;

    actuator->sendCommand(isYellow, id, vx, vy, vw);
}
