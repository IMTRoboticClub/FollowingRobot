#include "CommunicationManager.h"

//constante
char DEBUT_MESSAGE = '#';
char SEPARATOR = '\\';
char SEPARATOR_IN_BODY = '\\';
char FIN_MESSAGE = '$';
int BAUD = 9600;

CommunicationManager::CommunicationManager(int pinTX, int pinRX) : m_bluetooth(SoftwareSerial(pinTX, pinRX))
{

} 

void CommunicationManager::setup(int baud)
{
    m_bluetooth.begin(baud);
}

void CommunicationManager::listen()
{
    m_bluetooth.listen();
}


// renvoie vrai si tout le message a été récupéré
bool CommunicationManager::messageAnalyse()
{
    return messageFini;
}

void CommunicationManager::setMessage(String messageTest)
{
    messageLu = messageTest;
    messageFini = true;
    recupTypeCorps();
}

bool CommunicationManager::debutMessage(char charLu)
{
    return (charLu == DEBUT_MESSAGE);
}

bool CommunicationManager::finMessage(char charLu)
{
    return (charLu == FIN_MESSAGE);
}

/* recupere le message et le met dans l'attribut message, 
ne prend que le dernier message reconnu par le protocole, c'est à dire commançant par un # et finissant par finMessage
pour visualiser, utilisez visualiseMessage()

*/
void CommunicationManager::recupereMessage() 
{
    while (m_bluetooth.available() && !messageFini)
    {
        char charLu = m_bluetooth.read();
		

        if (debutMessage(charLu))
        {
            messageLu = "";
            messageFini = false;
        }
        if (!messageFini)
        {
			messageLu += charLu;
            messageFini = finMessage(charLu);
        }
        //Serial.print("in ");
        //Serial.println(messageFini);

    }
    
    //Serial.print("out ");
    //Serial.println(messageFini);
}


//permet de visualiser directement le message
void CommunicationManager::visualiseMessage()
{
    Serial.println(messageLu);
    if (messageFini)
    {
        Serial.println(messageLu);
    }
}

float CommunicationManager::byteToFloat(String intBit, unsigned int longueurIntBit) {

  unsigned int indexComa = 0;
  int valueInt = 0;
  int isNegative = 0;
  unsigned int indexDebut = 0;

  //on regarde si le premier caractere est - pour négatif
  if (intBit[0]=='-'){
      isNegative=1;
      indexDebut += 1;
  }

  //trouve l'index du point
  while (intBit[indexComa] != '.' && indexComa < longueurIntBit) {
    indexComa += 1;
  }

  //calcule la partie entière
  int puissance10 = 1;
  for (unsigned int index = indexDebut; index<indexComa-isNegative;index++) {

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
  float resu =valueInt + valueDecimal;

  if (isNegative)
  {
    resu = (-1)*resu;
  }

  return resu;
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
	//Serial.println("RecupTypeCorps");
    //on ne tient pas compte du caractere de debut
    unsigned int index = 1;

    while (messageLu[index] != SEPARATOR)
    {
        valueType += messageLu[index];
        index += 1;
    }
    
    index += 1;

    while (index < messageLu.length()-1)
    {
        valueBody += messageLu[index];
        index += 1;
    }
    m_typeMessage = stringToInt(valueType);
    m_corpsMessage = valueBody;
    
    Serial.print("RecupTypeCorps :");
    Serial.print(m_typeMessage);
    Serial.print("  ,");
    Serial.println(m_corpsMessage);
}

int CommunicationManager::getType()
{
    return m_typeMessage;
}

void CommunicationManager::traiteDonnees()
{
	Serial.print("traiteDonnes :");
	Serial.println(m_corpsMessage);
	
    int nbComponent=0;
    char charLu;
    String component;
    unsigned int nbChar = 0;
    while (nbChar < m_corpsMessage.length())
    {
      charLu = m_corpsMessage[nbChar];
      
      
      if (charLu == SEPARATOR_IN_BODY)
      {
        m_tableauCorpsDonnees[nbComponent] = component;
        nbComponent += 1;
        component = "";
        nbChar += 1; 
      }
      else
      {
        component += charLu;
        nbChar += 1; 
      }  
    }
    m_tableauCorpsDonnees[nbComponent] = component;
    nbComponent += 1;
    
    Serial.print("m_tableauCorpsDonnees : ");
	Serial.print(m_tableauCorpsDonnees[0]);
	Serial.print(" ");
	Serial.print(m_tableauCorpsDonnees[1]);
	Serial.print(" ");
	Serial.println(m_tableauCorpsDonnees[2]);
}

//si type 1
void CommunicationManager::recupereLongitude()
{
    String longitude=m_tableauCorpsDonnees[1];
    /*char charLu = m_corpsMessage[0];
    unsigned int nbChar = 0;
    while (charLu != SEPARATOR_IN_BODY and nbChar < m_corpsMessage.length()-1)
    {
        longitude += charLu;
        nbChar += 1;
        charLu = m_corpsMessage[nbChar];
    }*/
    
    m_longitude = longitude.toFloat();
    Serial.print("m_longitude : ");
	Serial.println(m_longitude);

    
}

void CommunicationManager::recupereLatitude()
{
    //on passe la longitude et on lit la latitude après le "/"
    /*char charLu = m_corpsMessage[0];
    unsigned int indexSlash = 0;
    while (charLu != SEPARATOR_IN_BODY && indexSlash < m_corpsMessage.length())
    {
        charLu = m_corpsMessage[indexSlash];
        indexSlash += 1;
    }*/
    
    String latitude=m_tableauCorpsDonnees[2];
    /*unsigned int nbChar = 0;

    while (nbChar < m_corpsMessage.length()-indexSlash)
    {
        charLu = m_corpsMessage[indexSlash +nbChar];
        latitude += charLu;
        nbChar += 1;
    }*/

    m_latitude = latitude.toFloat();
    Serial.print("m_latitude : ");
	Serial.println(m_latitude);
}

// créé par Baptiste use in analyseMessage
//Dans les 2 prochaines méthodes, le corps est composé d'un élément
//en théorie A VERIFIER
void CommunicationManager::recupereMode()
{
    if (m_tableauCorpsDonnees[0] == "libre")
    {
        m_mode = 1;
    }
    else if (m_tableauCorpsDonnees[0] == "controle")
    {
        m_mode = 0;
    }
}

// créé par Baptiste
void CommunicationManager::recupereMouvement()
{
    m_mouvement = m_tableauCorpsDonnees[0]; 
}

void CommunicationManager::analyseMessage()
{ 
	messageFini = false;
    recupereMessage();
    //Serial.print("messageFini ? ");
    //Serial.println(messageFini);
    //Serial.print("Out of recupereMessage ");
    //Serial.println(messageFini);
    
    if (messageFini) 
    {
        //Serial.print("In MessageFini ");
		//Serial.println(messageFini);
        recupTypeCorps();
       
        //Serial.print("Type du message ? ");
        //Serial.println(getType());
        traiteDonnees();//Baptiste selon moi arduino doit appeler analyseMessage au début et ensuite regarder le type puis faire ce qu'il faut faire
    }
}


float CommunicationManager::getLongitude()
{
	Serial.print("m_longitude avant envoi : ");
	Serial.println(m_longitude);
    return m_longitude;
}

float CommunicationManager::getLatitude()
{
	Serial.print("m_latitude avant envoi : ");
	Serial.println(m_latitude);
    return m_latitude;
}

//créé par Baptiste
int CommunicationManager::getMode()
{
    return m_mode;
}

//créé par Baptiste
String CommunicationManager::getMouvement()
{
    return m_mouvement;
}
