#include "MagneticRead.h"

float offset = 0;

MagneticRead::MagneticRead() 
{
    mag = Adafruit_HMC5883_Unified(12345);
}

void MagneticRead::setup()
{
    mag.begin();
}

float MagneticRead::getHeadingRad() 
{

    sensors_event_t event;
    mag.getEvent(&event);
  
    // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
    // Calculate heading when the magnetometer is level, then correct for signs of axis.
    double heading  = atan2(event.magnetic.y, event.magnetic.x);
    
    // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
    // Find yours here: http://www.magnetic-declination.com/
    // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
    // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
    float declinationAngle = 0.026;
    heading += declinationAngle;
    heading += offset;
    
    heading = Utils::nbModulo2PI(heading);
  
    return heading;
}

float MagneticRead::getHeadingDeg() 
{
    float heading = getHeadingRad()*Utils::radToDegree;
    return heading;
}