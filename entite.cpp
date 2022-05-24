#include "entite.h"
#include "var_globales.h"
#include "quadtree.h"
#include "rectangle.h"


/*******CLASSE ENTITE******/
Entite::Entite(){
    couleur = COLOR3FNUL;
}

Entite::Entite(int x, int y, int l, int h, Color3f c) :
    Rect (x, y, l, h) {
    couleur = c;
}

float Entite::GetColorR(){
    return couleur.r;
}
float Entite::GetColorV(){
    return couleur.v;
}
float Entite::GetColorB(){
    return couleur.b;
}

void Entite::draw(){
        glPushMatrix();
        glTranslatef(getX(), getY(),0.0);
            glColor3f(GetColorR(), GetColorV(), GetColorB());

            glBegin(GL_QUADS);
                glVertex2f(0,0);
                glVertex2f(getWidth(),0);
                glVertex2f(getWidth(),getHeight());
                glVertex2f(0,getHeight());
            glEnd();
        glPopMatrix();
    
}

const int Entite::quisuisje() {
    return INDEFINI;
}


/*******CLASSE DECORS*******/

Decors::Decors(int x, int y, int l, int h, Color3f c) :
    Entite (x, y, l, h, c) {
}


const int Decors::quisuisje() {
    return DECORS;
}


/*******CLASSE PERSONNAGE*******/

Personnage::Personnage(int x, int y, int l, int h, Color3f c) :
    Entite (x, y, l, h, c) {
        dans_portail = false;
}

const int Personnage::quisuisje() {
    return PERSONNAGE;
}

int Personnage::GetXarrivee(){
    return posarrivee.x;
}

void Personnage::PutXarrivee(int x){
    posarrivee.x = x;
}

int Personnage::GetYarrivee(){
    return posarrivee.y;
}

void Personnage::PutYarrivee(int y){
    posarrivee.y = y;
}

int Personnage::GetVitesseH(){
    return vitesse_h;
}

int Personnage::GetVitesseV(){
    return vitesse_v;
}

void Personnage::PutVitesseH(int vitesse){
    vitesse_h = vitesse;
}

void Personnage::PutVitesseV(int vitesse){
   vitesse_v = vitesse;
}

int Personnage::GetAccelerationH(){
    return acceleration_h;
}

int Personnage::GetAccelerationV(){
    return acceleration_v;
}

void Personnage::PutAccelerationH(int acceleration){
    acceleration_h = acceleration;
}

void Personnage::PutAccelerationV(int acceleration){
   acceleration_v = acceleration;
}

int Personnage::GetValAccelH(){
    return val_accel_h;
}

int Personnage::GetValAccelV(){
    return val_accel_v;
}

void Personnage::PutValAccelH(int acceleration){
    val_accel_h = acceleration;
}

void Personnage::PutValAccelV(int acceleration){
   val_accel_v = acceleration;
}

bool Personnage::est_dans_portail(){
    return dans_portail;
}

void Personnage::PutDansPortail(bool val){
    dans_portail = val;
}

int Personnage::GetIdPlateformeDessus(){
    return id_plateforme_dessus;
}

void Personnage::PutIdPlateformeDessus(int id){
    id_plateforme_dessus = id;
}

bool Personnage::EstSurPlateforme(){
    return (id_plateforme_dessus != -1);
}

void Personnage::AnnuleIdPlateformeDessus(){
    id_plateforme_dessus = -1;
}

Rect Personnage::RendRectArrivee(){
    return Rect (posarrivee.x, posarrivee.y, getWidth(), getHeight());
}


/*******CLASSE PORTAIL*******/


Portail::Portail(int x, int y, int l, int h, Color3f c) :
    Entite (x, y, l, h, c) {
}

const int Portail::quisuisje() {
    return PORTAIL;
}


/*****CLASSE PLATEFORME*****/
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

int Plateforme::GetVitesseV(){
    return vitesse_v;
}

void Plateforme::PutVitesseH(int vitesse){
    vitesse_h = vitesse;
}

void Plateforme::PutVitesseV(int vitesse){
   vitesse_v = vitesse;
}

int Plateforme::GetIdPersSurPlateforme(){
    return id_pers_sur_plateforme;
}
void Plateforme::PutIdPersSurPlateforme(int id){
    id_pers_sur_plateforme = id;
}
bool Plateforme::PersEstSurPlateforme(){
    return (id_pers_sur_plateforme != -1);
}

void Plateforme::AnnuleIdPersDessus(){
    id_pers_sur_plateforme = -1;
}

Rect Plateforme::RendRectArrivee(){
    return Rect (posarrivee.x, posarrivee.y, getWidth(), getHeight());
}
