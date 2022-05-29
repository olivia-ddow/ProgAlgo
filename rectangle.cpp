#include "rectangle.h"

Rect::Rect(){
    poscourante.x = 0;
    poscourante.y = 0;
    largeur = 0;
    hauteur = 0 ;
}

Rect::Rect(int x, int y, int l, int h){
    poscourante.x = x;
    poscourante.y =y;
    largeur = l;
    hauteur = h;
}

int Rect::getX(){
    return poscourante.x;
}

void Rect::putX(int x){
    poscourante.x = x;
}

int Rect::getY(){
    return poscourante.y;
}

void Rect::putY(int y){
    poscourante.y = y;
}

int Rect::getWidth(){
    return largeur;
}

int Rect::getHeight(){
    return hauteur;
}