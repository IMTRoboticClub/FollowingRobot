#ifndef GPS_h
#define GPS_h

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

class GPS
{
private:

    unsigned char*  recupDonneesBrut;
    bool ligneRecherchee = false;
    bool found = false;
    bool m_foundValueOnce = false;
    int tailleMessage = 0;

    const char message[7];
    int lenCharALire = 6;

    int nbCharLu;
    int lastNbCharLu;

    SoftwareSerial m_gps;

    float m_latPlateforme;
    float m_lonPlateforme;

    void clearBufferArray();
    float byteToFloat(unsigned char intBit[64], unsigned int longueurIntBit);
    bool separeDonneesRecu(unsigned char recupDonnees[128], unsigned int longueurDonnees[8], unsigned char dataReadable[8][64], int nbChar);

public:
    GPS(int pinTX, int pinRX);

    void setup();

    bool foundValue();
    bool foundValueOnce();

    float getLatitude();
    float getLongitude();

    void read1BitGPS();

};

#endif