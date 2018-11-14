#include "MagneticRead.h"

MagneticRead::MagneticRead() 
{
    mag = Adafruit_HMC5883_Unified(12345);
}

void MagneticRead::setup()
{
    mag.begin();
}

int MagneticRead::test()
{
    return 10;
}

float MagneticRead::getHeadingRad() 
{

    sensors_event_t event;
    mag.getEvent(&event);
  
    // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
    // Calculate heading when the magnetometer is level, then correct for signs of axis.
    float heading = atan2(event.magnetic.y, event.magnetic.x);
    
    // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
    // Find yours here: http://www.magnetic-declination.com/
    // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
    // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
    float declinationAngle = 0.026;
    heading += declinationAngle;
    
    // Correct for when signs are reversed.
    if(heading < 0)
      heading += 2*PI;
      
    // Check for wrap due to addition of declination.
    if(heading > 2*PI)
      heading -= 2*PI;
  
    return heading;
}

float MagneticRead::getHeadingDeg() 
{
    float heading = getHeadingRad()*180/M_PI;
    return heading;
}