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
  Point2D posarrivee;

public:
    Plateforme(int x, int y, int l, int h, Color3f c);
    const int quisuisje();
};
 
#endif