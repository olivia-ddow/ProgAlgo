#ifndef FONCTIONS_H
#define FONCTIONS_H
#include "entite.h"
#include <list>

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

//on teste la collision de la plateforme avec chaque entite
bool check_collision_plat_ent(bool inversion_vitesse, int i, list<int> liste_colli_plat);
//on teste la collision du pers sur la plateforme avec chaque entite
bool check_collision_pers_sur_plat_ent(bool inversion_vitesse, int id_pers, int i, list<int> liste_colli_pers);
//Check des collisions de la plateforme avec les personnages
bool check_collision_plat_pers(bool inversion_vitesse, int i);
//on teste la collision du pers sur la plateforme avec chaque pers
bool check_collision_pers_sur_plat_pers(bool inversion_vitesse, int id_pers, int i);
//Check collision entre plateformes
bool check_collision_plat_plat(bool inversion_vitesse, int i);
//on teste la collision du pers sur la plateforme avec chaque plateforme
bool check_collision_pers_sur_plat_plat(bool inversion_vitesse, int id_pers);
//calcul du delta entre la position d'arrivee et la pos courante de la plateforme 
//et du delta entre la position d'arrivee et la pos courante du pers uniquement si le pers est sur plateforme
void calcule_delta_pers_et_plateforme(int i, int id_pers);



#endif