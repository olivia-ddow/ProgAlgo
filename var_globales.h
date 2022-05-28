#ifndef VAR_GLOBALES_H
#define VAR_GLOBALES_H
#include "quadtree.h"
#include "memory"

//lu dans fichier txt
extern int largeur_map;
extern int hauteur_map;

//lu dans fichier txt
extern int val_accel_g;
extern int val_accel_f;
extern int val_max_vitesse_h;
extern int val_max_vitesse_v;

extern Quadtree qtree;
extern vector<shared_ptr<Entite>> liste_ent;

//lu dans fichier txt
extern int NB_PERS;
extern int NB_PLAT;
extern int NB_PORT;
extern int NB_ENT;

//Creer avec un new liste_plat à clear la liste à la fn du niveau
extern vector<Plateforme> liste_plat;
extern vector<Personnage> liste_pers;
extern vector<Entite> liste_btn;


#endif