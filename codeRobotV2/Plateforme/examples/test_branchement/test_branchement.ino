#include <Plateforme.h>

#define MOTEUR_G_PIN_G      4
//moteur gauche pin droite, etc
#define MOTEUR_G_PIN_D      5
#define MOTEUR_G_PIN_PWM    3
#define MOTEUR_D_PIN_G      9
#define MOTEUR_D_PIN_D      10
#define MOTEUR_D_PIN_PWM    11

Plateforme plateforme(MOTEUR_G_PIN_G, MOTEUR_G_PIN_D, MOTEUR_G_PIN_PWM, MOTEUR_D_PIN_G, MOTEUR_D_PIN_D, MOTEUR_D_PIN_PWM);


void setup() 
{
  plateforme.setup();

  plateforme.avance(220);
  delay(5000);

  plateforme.recule(220);
  delay(5000);

  plateforme.tournerAGauche();
  delay(5000);

  plateforme.tournerADroite();
  delay(5000);

}

void loop()
{
  
}

