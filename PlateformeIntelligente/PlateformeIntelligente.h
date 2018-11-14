#ifndef PLATEFORME_INTELLIGENTE_h
#define PLATEFORME_INTELLIGENTE_h

#include "Plateforme.h"

class PlateformeIntelligente : public Plateforme
{
private:


    //cette fonction ne doit être lancé que après avoir trouvé le bon angle
    void avancerJusque(int distance);
    void tournerJusque(double angle,double angleCible, int distance);
public:
    PlateformeIntelligente(int pinGaucheMGauche, int pinDroiteMGauche, int pinPWMMGauche, int pinGaucheMDroite, int pinDroiteMDroite, int pinPWMMDroite);

    void adapterVitesse(long distanceObjet);
    void rejoindreUtilisateur(double angle, double angleCible, int distance);

};

#endif