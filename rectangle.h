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
    void putX(int x);
    int getY();
    void putY(int y);
    int getWidth();
    int getHeight();
    //draw_rectangle();
};

#endif