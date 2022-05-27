#ifndef NIVEAU_MANAGER_H
#define NIVEAU_MANAGER_H

//variable de niveaux

const int NB_NIVEAUX_MAX = 4;
//0 menu
//1 intro
//2 premier niveau
//3 page de fin



extern int niveau_cpt;
extern int current_niveau;

void executer_niveau(int niveau_cpt);
void charger_niveau();
void jouer_niveau();

#endif
