#ifndef Coordonnee_h
#define Coordonnee_h

#include "math.h"
//Cette classe ne doit contenir que des radians !! 

class CoordonneeGPS
{
private:
    float m_latRad;
    float m_lonRad;
    
public:
    static float rayonTerrestre; //m
    static float radToDegree;

    CoordonneeGPS(float latRad, float lonRad);

    void setLatitude(float latitude);
    void setLongitude(float longitude);

    //calcule la longueur entre 2 coordonnée le long du rayon terrestre (suppose que la Terre est ronde)
    float longueurArcCercleTerrestre(CoordonneeGPS const& c2);
    
    float geoBearing(CoordonneeGPS const& b);
    
};

#endif