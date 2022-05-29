#ifndef ENTITE_H
#define ENTITE_H
#include "rectangle.h"
//#include <SDL2/SDL.h>
#if defined(_WIN32)
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;

/****CLASSE ENTITE******/
class Entite : public Rect {

private:
    Color3f couleur;

public: 
    Entite();
    Entite(int x, int y, int l, int h, Color3f c);
    virtual const int quisuisje();
    float GetColorR();
    float GetColorV();
    float GetColorB();
    void draw(int i);
};

/****CLASSE DECORS******/
class Decors : public Entite{
public:
    Decors(int x, int y, int l, int h, Color3f c);
    const int quisuisje();
};


/****CLASSE PERSONNAGE***/
class Personnage : public Entite{

private:
    //var a lire dans le fichier txt
    int val_accel_h;
    int val_accel_v; //equivalent constante 

    //var calculees
    Color3f couleurPerso;
    Point2D posarrivee;
    int vitesse_h; //horizontale
    int vitesse_v; //verticale
    int acceleration_h;
    int acceleration_v;
    bool dans_portail;
    int id_plateforme_dessus;


public:
    Personnage(int x, int y, int l, int h, Color3f c, int a_h, int a_v);
    const int quisuisje();
    void PutC(float rouge);
    int GetXarrivee();
    int GetYarrivee();
    void PutXarrivee(int x);
    void PutYarrivee(int y);
    int GetVitesseH();
    int GetVitesseV();
    void PutVitesseH(int vitesse);
    void PutVitesseV(int vitesse);
    int GetAccelerationH();
    int GetAccelerationV();
    void PutAccelerationH(int acceleration);
    void PutAccelerationV(int acceleration);
    int GetValAccelH();
    int GetValAccelV();
    void PutValAccelH(int acceleration);
    void PutValAccelV(int acceleration);
    bool est_dans_portail();
    void PutDansPortail(bool val);
    int GetIdPlateformeDessus();
    void PutIdPlateformeDessus(int id); 
    bool EstSurPlateforme();
    void AnnuleIdPlateformeDessus();
    Rect RendRectArrivee();
};

/****CLASSE PORTAIL***/
class Portail : public Entite {
private:
    Point2D posarrivee;

public:
    Portail(int x, int y, int l, int h, Color3f c);
    const int quisuisje();
};


/****CLASSE PLATEFORME***/
class Plateforme : public Entite {
private:
  int vitesse_h; //horizontale
  int vitesse_v; //verticale
  Point2D posarrivee;
  int id_pers_sur_plateforme;

public:
    Plateforme();
    Plateforme(int x, int y, int l, int h, Color3f c, int v_h, int v_v);

    const int quisuisje();
    int GetXarrivee();
    int GetYarrivee();
    void PutXarrivee(int x);
    void PutYarrivee(int y);
    int GetVitesseH();
    int GetVitesseV();
    void PutVitesseH(int vitesse);
    void PutVitesseV(int vitesse);
    int GetIdPersSurPlateforme();
    void PutIdPersSurPlateforme(int id);
    bool PersEstSurPlateforme();
    void AnnuleIdPersDessus();
    Rect RendRectArrivee();
};

#endif