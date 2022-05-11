#include "entite.h"

Entite::Entite(){
    couleur = COLOR3FNUL;
}

Entite::Entite(int x, int y, int l, int h, Color3f c) :
    Rectangle (x, y, l, h) {
    couleur = c;
}

const int Entite::quisuisje() {
    return INDEFINI;
}

Decors::Decors(int x, int y, int l, int h, Color3f c) :
    Entite (x, y, l, h, c) {
}


const int Decors::quisuisje() {
    return DECORS;
}

Personnage::Personnage(int x, int y, int l, int h, Color3f c) :
    Entite (x, y, l, h, c) {
}

const int Personnage::quisuisje() {
    return PERSONNAGE;
}

Portail::Portail(int x, int y, int l, int h, Color3f c) :
    Entite (x, y, l, h, c) {
}

const int Portail::quisuisje() {
    return PORTAIL;
}

Plateforme::Plateforme(int x, int y, int l, int h, Color3f c) :
    Entite (x, y, l, h, c) {
}

const int Plateforme::quisuisje() {
    return PLATEFORME;
}