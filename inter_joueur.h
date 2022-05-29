#ifndef INTER_JOUEUR_H
#define INTER_JOUEUR_H
#include <SDL2/SDL.h>
// use lodepng instead
// #include <SDL2/SDL_image.h>
#if defined(_WIN32)
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

enum TypeChoix {CHOIX_INDEFINI = 0, 
                QUITTER_JEU = SDLK_DELETE,
                GAUCHE = SDLK_q,
                DROITE = SDLK_d, 
                SAUT = SDLK_z, 
                TAB = SDLK_TAB};

extern TypeChoix choix_joueur;

extern int pers_select;

//execute le choix du joueur
void executer_choix_joueur();
//deplacements du joueur
void deplacer_joueur();

//VITESSE HORIZONTALE
void calcule_vitesse_h_pers(int i);
//VITESSE VERTICALE
void calcule_vitesse_v_pers(int i);
//CHECK COLLISION ENTITE STATIQ
void check_collision_pers_ent(int i);
//CHECK COLLI AVEC AUTRES PERSONNAGES
void check_collision_pers_pers(int i);
//CHECK COLLI AVEC PLATEFORMES
void check_collision_pers_plat(int i);



#endif