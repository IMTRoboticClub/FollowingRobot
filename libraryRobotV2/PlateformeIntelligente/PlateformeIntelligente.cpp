#include "PlateformeIntelligente.h"

//cette fonction ne doit être lancé que après avoir trouvé le bon angle
void PlateformeIntelligente::avancerJusque(int distance)
{

  if (distance>50)// (ouais mais une fonction continue c'est mieux) l'idée ici est d' adapter la vitesse à la distance à l'utilisateur (imagine une voiture qui roule à 100 et qui décide de s'arreter à un feu alors qu'il est à 10 metres de celui ci
  {
    avance(100);
  }
  else if (distance>10)
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
    int angleBis= angleCible - angle;
    while(angleBis<0)
    {
        angleBis=angleBis+360;
    }
    if (7<angleBis && angleBis<=180) //tourner à droite // ici on dit que pour 2 degrés on accepte d'aller tout droit
    {
        tournerADroite();
    }
    else if (180< angleBis && angleBis <= 352) //tourner à gauche
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