#ifndef QUADTREE_H
#define QUADTREE_H

#include <list>
#include "rectangle.h"
#include "entite.h"
using namespace std;

const int NB_OBJ_MAX = 4;

class Quadtree {
 
private :
    list<int> liste_index_entite;
    Rectangle conteneur;
    Quadtree * fils[4] = {nullptr};
    void separer();
    int donnePartieQuad(Rectangle rect);
    int donneNbEntites();
    list<int> recupIdToutesEntites(list<int> l_id_entites);
    

public:
    Quadtree();
    Quadtree(Rectangle cont);
    void definir_rect(Rectangle cont);
    void effacer_fils();
    bool est_feuille();
    bool intersection_non_nulle(Rectangle r1, Rectangle r2);
    //bool intersection_strict_non_nulle(Rectangle r1, Rectangle r2);
    void insert_id_entite(int indexTab);
    //recupere une liste de noeuds feuille qui contiennent le rectangle cible
    list<Quadtree> recupere_noeuds(list<Quadtree> noeuds_recup, Rectangle rect);
    //recupere une liste d'index des entites succeptibles d'avoir une collision avec le rectangle
    list<int> recupere_id_entites(list<int> l_entites_recup, Rectangle rect);
    void supprime_id_entite(int index_ent);
};  

#endif