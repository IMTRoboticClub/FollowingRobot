#include "Coordonnee.h"

float CoordonneeGPS::rayonTerrestre = 6371000;
float CoordonneeGPS::radToDegree = 57.295779513082320876f;

CoordonneeGPS::CoordonneeGPS(float latRad, float lonRad)
{
  m_latRad = latRad;
  m_lonRad = lonRad;
}

void CoordonneeGPS::setLatitude(float latitude)
{
  m_latRad = latitude;
}

void CoordonneeGPS::setLongitude(float longitude)
{
  m_lonRad = longitude;
}

float CoordonneeGPS::longueurArcCercleTerrestre(CoordonneeGPS const& c2)
{
  float lat1 = this->m_latRad;
  float lat2 = c2.m_latRad;
  float diffLat = c2.m_latRad-this->m_latRad;
  float diffLon = c2.m_lonRad-this->m_lonRad;

  float x = sin(diffLat/2) * sin(diffLat/2) + cos(lat1) * cos(lat2) * sin(diffLon/2) * sin(diffLon/2);
  float y = 2 * atan2(sqrt(x), sqrt(1-x));

  return rayonTerrestre * y;
}

float CoordonneeGPS::geoBearing(CoordonneeGPS const& b) 
{
  float y = sin(b.m_lonRad-this->m_lonRad) * cos(b.m_latRad);
  float x = cos(this->m_latRad)*sin(b.m_latRad) - sin(this->m_latRad)*cos(b.m_latRad)*cos(b.m_lonRad-this->m_lonRad);
  return atan2(y, x) * radToDegree;
}