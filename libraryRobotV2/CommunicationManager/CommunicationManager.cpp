#include "CommunicationManager.h"

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
        if (!messageFini)
        {
            messageLu += charLu;
            messageFini = finMessage();
        }
    }
}

float CommunicationManager::byteToFloat(String intBit, unsigned int longueurIntBit) {

  //trouve l'index du point
  int indexComa = 0;
  int valueInt = 0;
  while (intBit[indexComa] != '.' && indexComa < longueurIntBit) {
    indexComa += 1;
  }

  //calcule la partie entière
  int puissance10 = 1;
  for (int index =0; index<indexComa;index++) {
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

    for (index; index < messageLu.length()-LEN_FIN_MESSAGE; index++)
    {
        valueBody += messageLu[index];
    }
    
    m_typeMessage = stringToInt(valueType);
    m_corpsMessage = valueBody;
}


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

void CommunicationManager::analyseMessage()
{
    recupereMessage();
    if (messageFini) 
    {
        if (m_typeMessage == POSITION)
        {
            
            m_latitude = recupereLatitude();
            m_longitude = recupereLongitude();
        }
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