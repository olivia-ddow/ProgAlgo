#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "structs_gen.h"

class Rectangle {

private:
    Point2D poscourante;
    int largeur;
    int hauteur;

public:
    Rectangle();
    Rectangle(int x, int y, int l, int h);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
};

#endif