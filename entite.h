#ifndef ENTITE_H
#define ENTITE_H
#include "rectangle.h"
using namespace std;

class Entite : public Rectangle {

private:
    Color3f couleur;

public: 
    Entite();
    Entite(int x, int y, int l, int h, Color3f c);
    virtual const int quisuisje();
};

class Decors : public Entite{
public:
    Decors(int x, int y, int l, int h, Color3f c);
    const int quisuisje();
};

class Personnage : public Entite{

private:
    Point2D posarrivee;

public:
    Personnage(int x, int y, int l, int h, Color3f c);
    const int quisuisje();
};

class Portail : public Entite {
private:
    Point2D posarrivee;

public:
    Portail(int x, int y, int l, int h, Color3f c);
    const int quisuisje();
};

class Plateforme : public Entite {
private:
  int vitesse_h; //horizontale
  int vitesse_v; //verticale
  Point2D posarrivee;

public:
    Plateforme();
    Plateforme(int x, int y, int l, int h, Color3f c);

    const int quisuisje();
    int GetXarrivee();
    int GetYarrivee();
    void PutXarrivee(int x);
    void PutYarrivee(int y);
    int GetVitesseH();
    int GetVitesseV();
    void PutVitesseH(int vitesse);
    void PutVitesseV(int vitesse);
};
 
#endif