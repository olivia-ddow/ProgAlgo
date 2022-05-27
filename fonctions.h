#ifndef FONCTIONS_H
#define FONCTIONS_H
#include "entite.h"

//Detection Collision
bool intersection_non_nulle(Rect * r1, Rect *r2);
bool intersection_strict_non_nulle(Rect *r1, Rect *r2);
//change le personnage selectionne
int changer_selection(int pers_selectionne);
//Retourne si deux rectangles ont les memes dimensions
bool taille_rec_est_identique(Rect *rec1, Rect *rec2);
//Retourne si tous les personnages qui sont dans les portails
bool personnages_sont_dans_portails();
//deplacements des plateformes
void deplacer_plateformes();
#endif