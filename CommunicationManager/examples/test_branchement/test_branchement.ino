#include <CommunicationManager.h>
#include <Coordonnee.h>

#define POSITION 1
#define START 2
#define STOP 3


CommunicationManager communicationManager(8, 2);
CoordonneeGPS coordonneeAndroidtest1(-1,-1);

int orderToPlatform;
void setup()
{
  Serial.begin(9600);
  communicationManager.setup(9600);
  
}

void loop()
{
  
  communicationManager.recupereMessage();
  communicationManager.visualiseMessage();

//    if (communicationManager.messageAnalyse()){
//    communicationManager.visualiseMessage();
//    int typeRecu = communicationManager.getType();
//    if (typeRecu == POSITION)
//    {
//      Serial.println(communicationManager.getLongitude());
//      Serial.println(communicationManager.getLatitude());
//        coordonneeAndroidtest1.setLatitude(communicationManager.recupereLatitude());
//        coordonneeAndroidtest1.setLongitude(communicationManager.recupereLongitude());
//    }
//    else if (typeRecu == START)
//    {
//      orderToPlatform = START;  
//    }
//    else if (typeRecu == STOP)
//    {
//      orderToPlatform = STOP;
//    }
  

//  }
}

