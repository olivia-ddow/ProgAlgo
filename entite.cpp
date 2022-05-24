#include "entite.h"
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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

float Entite::GetColorR(){
    return couleur.r;
}
float Entite::GetColorV(){
    return couleur.v;
}
float Entite::GetColorB(){
    return couleur.b;
}

void Entite::draw(int i){
        glPushMatrix();
        glTranslatef(getX(), getY(),0.0);

            // si i=0 on va attribuer une couleur à notre entité, si il est égal à autre chose (1) alors on lui appliquera une texture
            if (i==0){
                glColor3f(GetColorR(), GetColorV(), GetColorB());
            }
            
            glBegin(GL_QUADS);
                
                

                glTexCoord2f(0,0); 
                glVertex2f(0,getHeight());
                
                glTexCoord2f(0,1);
                glVertex2f(0,0);

                glTexCoord2f(1,1);
                
                glVertex2f(getWidth(),0);
                glTexCoord2f(1,0);
                
                glVertex2f(getWidth(),getHeight());
            glEnd();
        glPopMatrix();
    
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