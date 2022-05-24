#include "quadtree.h"
#include "entite.h"
#include "structs_gen.h"
#include "test.h"
#include "var_globales.h"
#include "niveau_manager.h"
#include "fonctions.h"
#include "inter_joueur.h"
#include "interf_graph.h"

#include <vector>
#include <iostream>
using namespace std;

int largeur_map = 0;
int hauteur_map = 0;

int val_accel_g = 0;
int val_accel_f = 0;
int val_max_vitesse_h = 0;
int val_max_vitesse_v = 0;

int NB_PERS = 0;
int NB_PLAT = 0;
int NB_PORT = 0;
int NB_ENT = 0;


vector<Entite> liste_ent;
vector<Personnage> liste_pers = {Personnage(100, 50, 50, 20, {0.1,0.3,0.9})};

vector<Plateforme> liste_plat = {Plateforme(10, 10, 300, 30, {0.1,0.8,0.9})};

Quadtree qtree;

int main() {
    std::cout << "Hello World" << std::endl;
    //test(); 
    //TODO
    //fenetre debut
    while (niveau_cpt != NB_NIVEAUX_MAX && choix_joueur != QUITTER_JEU){
        executer_niveau(niveau_cpt);
    }
    //fenetre_fin
    return 0;  
}
