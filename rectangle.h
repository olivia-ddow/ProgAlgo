#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "structs_gen.h"

class Rect {

private:
    Point2D poscourante;
    int largeur;
    int hauteur;

public:
    Rect();
    Rect(int x, int y, int l, int h);
    int getX();
    void putX(int x);
    int getY();
    void putY(int y);
    int getWidth();
    int getHeight();
    //draw_rectangle(); TODO
};

const Rect RECTNUL = {0,0,0,0};
#endif