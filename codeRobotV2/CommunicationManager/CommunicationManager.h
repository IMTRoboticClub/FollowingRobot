#ifndef CommunicationManager_h
#define CommunicationManager_h

#include <Arduino.h>
#include <SoftwareSerial.h>


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
    int m_mode;
    char m_mouvement;

    //même répartition pour les méthodes

    bool debutMessage(char charLu);
    bool finMessage();

    //fonctions utiles pour le traitement
    float byteToFloat(String intBit, unsigned int longueurIntBit);
    int stringToInt(String value);

    void recupTypeCorps();

public:
    CommunicationManager(int pinTX, int pinRX);

    void setup();

    void recupereMessage();
    void visualiseMessage();

    int getType();

    void analyseMessage();
    bool messageAnalyse();

    String setMessage(String messageTest);

    //passe du corps de message aux données
    //type 1
    float recupereLatitude();
    float recupereLongitude();
    //type 5
    int recupereMode();
    //type 8
    char recupereMouvement();

    float getLatitude();
    float getLongitude();

    int getMode();
    char getMouvement();

};

#endif