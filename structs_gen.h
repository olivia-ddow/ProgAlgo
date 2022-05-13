#ifndef STRUCTS_GEN_H
#define STRUCTS_GEN_H
#include <vector>
using namespace std;

typedef struct {
    int x;
    int y;
} Point2D;

typedef struct {
    float r;
    float v;
    float b;
} Color3f;

const Color3f COLOR3FNUL = {0.0,0.0,0.0};

enum TypeRect {INDEFINI, DECORS, PERSONNAGE, PLATEFORME, PORTAIL};

#endif