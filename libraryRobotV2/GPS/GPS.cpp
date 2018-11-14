#include "GPS.h"

GPS::GPS(int pinTX, int pinRX) :message {'$', 'G', 'P', 'G', 'L', 'L'}, m_gps(pinTX, pinRX), m_latPlateforme(-1), m_lonPlateforme(-1), nbCharLu(0)
{
  recupDonneesBrut = new unsigned char[128];
}

void GPS::setup() {
  m_gps.begin(9600);
}

float GPS::getLatitude()
{
    return m_latPlateforme;
}

float GPS::getLongitude()
{
    return m_lonPlateforme;
}

bool GPS::foundValue() 
{
  return found;
}

float GPS::byteToFloat(unsigned char intBit[64], unsigned int longueurIntBit) {

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

//return true if the data are correct, false if the gps is not appaired
//conditionGPSNonconnecté compte le nombre de virgules
bool GPS::separeDonneesRecu(unsigned char recupDonnees[128], unsigned int longueurDonnees[8], unsigned char dataReadable[8][64], int nbChar) {
  int charInCurrentField = 0;
  int conditionGPSNonConnecte =0;
  unsigned int field = 0;
  for (int i ; i < nbChar;i++) {
      if (recupDonnees[i] == ',') {
        longueurDonnees[field] = charInCurrentField;
        field += 1;
        charInCurrentField = 0;
        if (conditionGPSNonConnecte == 3){
          return false;
        }

        conditionGPSNonConnecte +=1;
      }
      else {
        dataReadable[field][charInCurrentField] = recupDonnees[i];
        charInCurrentField +=1;

        conditionGPSNonConnecte=0;
      }
  }
  return(true);
}

void GPS::read1BitGPS()
{
    unsigned char value;
    found = false;
    if(m_gps.available())
    {

      value = m_gps.read();
      
      //si on lit une nouvelle ligne, on réinitialise les données et traite les informations si elles nous intéressent
      if (value == '$') {
        if (ligneRecherchee) {
          unsigned int longueurDonnees[8];
          unsigned char dataReadable[8][64];
          if (separeDonneesRecu(recupDonneesBrut, longueurDonnees, dataReadable, nbCharLu))
          {
            m_latPlateforme = byteToFloat(dataReadable[1], longueurDonnees[1]);
            found = true;
            m_lonPlateforme = byteToFloat(dataReadable[3], longueurDonnees[3]);
          }
          else
          {

          }
          lastNbCharLu = nbCharLu;
        }
        ligneRecherchee = true;
        nbCharLu = 0;
    
      }


      if (value == message[nbCharLu] || nbCharLu >= lenCharALire) {
        
          recupDonneesBrut[nbCharLu] = value;
          
      }
      else {
        ligneRecherchee = false;
      }
      nbCharLu += 1;
    }
}