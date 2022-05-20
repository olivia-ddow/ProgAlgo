#ifndef INTER_JOUEUR_H
#define INTER_JOUEUR_H

enum TypeChoix {CHOIX_INDEFINI, QUITTER_JEU, MENU, GAUCHE, DROITE, SAUT, SELECT};

extern TypeChoix choix_joueur;

extern int pers_select;

//execute le choix du joueur
void executer_choix_joueur();
//deplacements du joueur
void deplacer_joueur();

#endif