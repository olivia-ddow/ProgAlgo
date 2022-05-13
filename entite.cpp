#include "entite.h"
#include "var_globales.h"
#include "quadtree.h"

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

Plateforme::Plateforme(){
    vitesse_h = 0;
    vitesse_v = 0;
    posarrivee = POINT2DNUL;
}

Plateforme::Plateforme(int x, int y, int l, int h, Color3f c) :
    Entite (x, y, l, h, c) {
}

const int Plateforme::quisuisje() {
    return PLATEFORME;
}

int Plateforme::GetXarrivee(){
    return posarrivee.x;
}

void Plateforme::PutXarrivee(int x){
    posarrivee.x = x;
}

int Plateforme::GetYarrivee(){
    return posarrivee.y;
}

void Plateforme::PutYarrivee(int y){
    posarrivee.y = y;
}

int Plateforme::GetVitesseH(){
    return vitesse_h;
}

void Plateforme::PutVitesseH(int vitesse){
    vitesse_h = vitesse;
}

void Plateforme::PutVitesseV(int vitesse){
   vitesse_v = vitesse;
}
