#ifndef DETECTION_OBSTACLE_h
#define DETECTION_OBSTACLE_h

#include "Arduino.h"

class DetectionObstacle 
{
private:
    int m_pinTrig;
    int m_pinEcho;

public:
    DetectionObstacle(int pinTrig, int pinEcho);

    void setup();

    long recupDistanceCM();
    float recupDistanceM();

};

#endif