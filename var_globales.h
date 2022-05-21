#ifndef VAR_GLOBALES_H
#define VAR_GLOBALES_H
#include "quadtree.h"

//lu dans fichier txt
extern int largeur_map;
extern int largeur_map;

//lu dans fichier txt
extern int val_accel_g;
extern int val_accel_f;
extern int val_max_vitesse_h;
extern int val_max_vitesse_v;

extern Quadtree qtree;
extern vector<Entite> liste_ent;

//lu dans fichier txt
extern int NB_PERS;
extern int NB_PLAT;
extern int NB_PORT;
extern int NB_ENT;



//clear à la fin du niveau
extern vector<Personnage> liste_pers;
extern vector<Plateforme> liste_plat;

#endif