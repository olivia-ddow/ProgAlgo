#ifndef STRUCTS_GEN_H
#define STRUCTS_GEN_H
#include <vector>
using namespace std;

typedef struct {
    int x;
    int y;
} Point2D;

const Point2D POINT2DNUL= {0,0};

typedef struct {
    int r;
    int v;
    int b;
} Color3f;

const Color3f COLOR3FNUL = {0,0,0};

enum TypeRect {INDEFINI, DECORS, PERSONNAGE, PLATEFORME, PORTAIL};

#endif