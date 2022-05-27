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
                MENU = SDLK_m,
                GAUCHE = SDLK_q,
                DROITE = SDLK_d, 
                SAUT = SDLK_SPACE, 
                SELECT = SDLK_RETURN};

extern TypeChoix choix_joueur;

extern int pers_select;

//execute le choix du joueur
void executer_choix_joueur();
//deplacements du joueur
void deplacer_joueur();

#endif