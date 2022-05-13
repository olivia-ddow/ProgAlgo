#ifndef VAR_GLOBALES_H
#define VAR_GLOBALES_H
#include "quadtree.h"

extern Quadtree qtree;
extern vector<Entite> liste_ent;
extern int NB_PERS;
extern int NB_PLAT;
//Creer avec un new liste_plat à delete à la fn du niveau
extern Plateforme liste_plat[];
extern Personnage liste_pers[];
#endif