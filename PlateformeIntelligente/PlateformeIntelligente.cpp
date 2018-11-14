#include "PlateformeIntelligente.h"

PlateformeIntelligente::PlateformeIntelligente(int pinGaucheMGauche, int pinDroiteMGauche, int pinPWMMGauche, int pinGaucheMDroite, int pinDroiteMDroite, int pinPWMMDroite) : Plateforme(pinGaucheMGauche, pinDroiteMGauche, pinPWMMGauche, pinGaucheMDroite, pinDroiteMDroite, pinPWMMDroite)
{

}

//cette fonction ne doit être lancé que après avoir trouvé le bon angle
void PlateformeIntelligente::avancerJusque(int distance)
{
  if (distance < 0)
  {
    stop();
  }
  if (distance>50)// (ouais mais une fonction continue c'est mieux) l'idée ici est d' adapter la vitesse à la distance à l'utilisateur (imagine une voiture qui roule à 100 et qui décide de s'arreter à un feu alors qu'il est à 10 metres de celui ci
  {
    avance(100);
  }
  else if (50 > distance && distance>10)
  {
    avance(50);
  }
  else
  {
    stop();
  }
}


void PlateformeIntelligente::tournerJusque(double angle,double angleCible, int distance)
{
  if (angle < 0 || angleCible < 0)
  {
    stop();
    return;
  }
  
  int angleBis= angleCible - angle;
  while(angleBis<0)
  {
      angleBis=angleBis+360;
  }
  if (30<angleBis && angleBis<=180) //tourner à droite // ici on dit que pour 2 degrés on accepte d'aller tout droit
  {
      tournerADroite();
  }
  else if (180< angleBis && angleBis <= 330) //tourner à gauche
  {
      tournerAGauche(); //idem que juste au dessus
  }
  else
  {
      avancerJusque(distance);
  }
}

void PlateformeIntelligente::adapterVitesse(long distanceObjet)
{

}

void PlateformeIntelligente::rejoindreUtilisateur(double anglePlateformeAvecNord, double angleCible, int distance)
{
    tournerJusque(anglePlateformeAvecNord, angleCible, distance);
}