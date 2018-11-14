#include <CommunicationManager.h>

String fin_message = "\\n\\r";

CommunicationManager comm(8, 2, fin_message);

void setup()
{
  Serial.begin(9600);
  comm.setup();
}

void loop()
{
  comm.analyseMessage();
  if (comm.messageAnalyse())
  {
    Serial.println(comm.getLongitude());
    Serial.println(comm.getLatitude());
  }

}

