#include "CommunicationManager.h"

//constante
char DEBUT_MESSAGE = '#';
char SEPARATOR = '\\';
char SEPARATOR_IN_BODY = '\\';
String FIN_MESSAGE = "\\n\\r";
int LEN_FIN_MESSAGE = 4;

CommunicationManager::CommunicationManager(int pinTX, int pinRX) : m_bluetooth(SoftwareSerial(pinTX, pinRX))
{

} 

void CommunicationManager::setup()
{
    m_bluetooth.begin(9600);
}

bool CommunicationManager::messageAnalyse()
{
    return messageFini;
}

String CommunicationManager::setMessage(String messageTest)
{
    Serial.println(messageTest);
    messageLu = messageTest;
    messageFini = true;
    recupTypeCorps();
}

bool CommunicationManager::debutMessage(char charLu)
{
    return (charLu == DEBUT_MESSAGE);
}

bool CommunicationManager::finMessage()
{
    int indexDebutComparaison = messageLu.length()-LEN_FIN_MESSAGE; 
    bool messageFini = false;
    if (indexDebutComparaison >= 0)
    {
        messageFini = true;
        for (int index = 0; index < LEN_FIN_MESSAGE; index++)
        {
            messageFini = messageFini && (messageLu[indexDebutComparaison + index] == FIN_MESSAGE[index]);
        }
    }
    return messageFini;
}

void CommunicationManager::recupereMessage() 
{
    while (m_bluetooth.available())
    {
        char charLu = m_bluetooth.read();
        if (debutMessage(charLu))
        {
            messageLu = "" + charLu;
            messageFini = false;
        }
        Serial.println(messageLu);
        if (!messageFini)
        {
            messageLu += charLu;
            messageFini = finMessage();
        }
    }
}

void CommunicationManager::visualiseMessage()
{
    if (messageFini)
    {
        Serial.println(messageLu);
    }
}

float CommunicationManager::byteToFloat(String intBit, unsigned int longueurIntBit) {

  //trouve l'index du point
  unsigned int indexComa = 0;
  int valueInt = 0;
  while (intBit[indexComa] != '.' && indexComa < longueurIntBit) {
    indexComa += 1;
  }

  //calcule la partie entière
  int puissance10 = 1;
  for (unsigned int index =0; index<indexComa;index++) {
    valueInt += (int(intBit[indexComa-1-index])-48)*puissance10;
    puissance10 *= 10;
  }
  puissance10 = 10;

  //calcule la partie décimale
  float valueDecimal = 0;
  for (unsigned int index = indexComa+1; index<longueurIntBit; index ++)
  {
    valueDecimal += (float(intBit[index])-48)/puissance10;
    puissance10 *= 10;
  }
  return valueInt + valueDecimal;
}

//Pour l'instant ne renvoie que le premier chiffre du string
int CommunicationManager::stringToInt(String value)
{
    return int(value[0])-48;
}

void CommunicationManager::recupTypeCorps()
{
    String valueType = "";
    String valueBody = "";

    //on ne tient pas compte du caractere de debut
    unsigned int index = 1;

    while (messageLu[index] != SEPARATOR)
    {
        valueType += messageLu[index];
        index += 1;
    }
    index += 1;

    while (index < messageLu.length()-LEN_FIN_MESSAGE)
    {
        valueBody += messageLu[index];
        index += 1;
    }
    
    m_typeMessage = stringToInt(valueType);
    m_corpsMessage = valueBody;
    Serial.println(m_corpsMessage);
}

int CommunicationManager::getType()
{
    return m_typeMessage;
}

//si type 1
float CommunicationManager::recupereLongitude()
{
    String longitude;
    char charLu = m_corpsMessage[0];
    unsigned int nbChar = 0;
    while (charLu != SEPARATOR_IN_BODY and nbChar < m_corpsMessage.length()-1)
    {
        longitude += charLu;
        nbChar += 1;
        charLu = m_corpsMessage[nbChar];
    }
    return byteToFloat(longitude, longitude.length());
}

float CommunicationManager::recupereLatitude()
{
    //on passe la longitude et on lit la latitude après le "/"
    char charLu = m_corpsMessage[0];
    unsigned int indexSlash = 0;
    while (charLu != SEPARATOR_IN_BODY && indexSlash < m_corpsMessage.length())
    {
        charLu = m_corpsMessage[indexSlash];
        indexSlash += 1;
    }
    
    String latitude;
    unsigned int nbChar = 0;

    while (nbChar < m_corpsMessage.length()-indexSlash)
    {
        charLu = m_corpsMessage[indexSlash +nbChar];
        latitude += charLu;
        nbChar += 1;
    }

    return byteToFloat(latitude, nbChar);
}

// créé par Baptiste use in analyseMessage
//Dans les 2 prochaines méthodes, le corps est composé d'un élément
//en théorie A VERIFIER
int CommunicationManager::recupereMode()
{
    return( stringToInt(m_corpsMessage)); 
}

// créé par Baptiste
char CommunicationManager::recupereMouvement()
{
    return( stringToInt(m_corpsMessage)); 
}

void CommunicationManager::analyseMessage()
{
    recupereMessage();
    if (messageFini) 
    {
        recupTypeCorps();
        
    }
}


float CommunicationManager::getLongitude()
{
    return m_longitude;
}

float CommunicationManager::getLatitude()
{
    return m_latitude;
}

//créé par Baptiste
int CommunicationManager::getMode()
{
    return m_mode;
}
//créé par Baptiste
char CommunicationManager::getMouvement()
{
    return m_mouvement;
}