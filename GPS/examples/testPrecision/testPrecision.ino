#include <GPS.h>

GPS gps(6, 7);

void setup() {
  Serial.begin(9600);
  Serial.println("bonjour");
  
  gps.setup();
}

void loop() {
  gps.recupDonnees();
  gps.retrieveData();
  if (gps.connected())
  {
    
    Serial.print("latitude du robot : ");
    Serial.print(gps.getLatitudeDeg(), 8);
    Serial.print("   longitude du robot : ");
    Serial.println(gps.getLongitudeDeg(), 8);
    
  }
}
