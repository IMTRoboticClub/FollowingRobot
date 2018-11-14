#ifndef MagneticRead_h
#define MagneticRead_h

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

class MagneticRead
{
private:
    Adafruit_HMC5883_Unified mag;

public:
    MagneticRead();

    void setup();

    int test();

    float getHeadingRad();
    float getHeadingDeg();
};

#endif