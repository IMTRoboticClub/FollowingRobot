#include <GPS.h>

#define PIN_GAUCHE 5
#define PIN_DROITE 4
#define PIN_PWM 3

GPS gps(6, 7);

void setup() {
  Serial.begin(9600);
  
  gps.setup();
}

void loop() {
  gps.read1BitGPS();
  if (gps.foundValue())
  {
    
  Serial.print("Victoire : ");
  Serial.println(gps.getLatitude());
  }
}
