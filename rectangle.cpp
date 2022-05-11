#include "rectangle.h"

Rectangle::Rectangle(){
    poscourante.x = 0;
    poscourante.y = 0;
    largeur = 0;
    hauteur = 0 ;
}
Rectangle::Rectangle(int x, int y, int l, int h){
    poscourante.x = x;
    poscourante.y =y;
    largeur = l;
    hauteur = h;
}

int Rectangle::getX(){
    return poscourante.x;
}

int Rectangle::getY(){
    return poscourante.y;
}

int Rectangle::getWidth(){
    return largeur;
}

int Rectangle::getHeight(){
    return hauteur;
}