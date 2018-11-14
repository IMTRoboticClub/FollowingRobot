#ifndef CommunicationManager_h
#define CommunicationManager_h

#include <Arduino.h>
#include <SoftwareSerial.h>

//constante
char DEBUT_MESSAGE = '#';
char SEPARATOR = '/';
char SEPARATOR_IN_BODY = '/';
String FIN_MESSAGE = "\\n\\r";
int LEN_FIN_MESSAGE = 4;

enum type {
    POSITION = 1
};

class CommunicationManager
{
private:
    SoftwareSerial m_bluetooth;

    //Utilisé pour lire le message via bluetooth
    String messageLu;
    bool messageFini;

    //Utilisé pour traiter le message une fois lu 
    int m_typeMessage;
    String m_corpsMessage;

    //données qui seront fourni à l'arduino
    float m_latitude;
    float m_longitude;

    //même répartition pour les méthodes

    bool debutMessage(char charLu);
    bool finMessage();
    void recupereMessage();

    //fonctions utiles pour le traitement
    float byteToFloat(String intBit, unsigned int longueurIntBit);
    int stringToInt(String value);

    void recupTypeCorps();

    //passe du corps de message aux données
    //type 1
    float recupereLatitude();
    float recupereLongitude();

public:
    CommunicationManager(int pinTX, int pinRX);

    void setup();

    void analyseMessage();
    bool messageAnalyse();

    float getLatitude();
    float getLongitude();


};

#endif