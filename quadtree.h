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
    Rect conteneur;
    Quadtree * fils[4] = {nullptr};
    //Separe le conteneur du noeud en 4 parties
    void separer();
    //renvoie la partie du QuadTree dans lequel se trouve le rectangle, si le rectangle chevauche plusieurs parties retourne -1
    int donnePartieQuad(Rect rect);
    //renvoie le nb d'entites dans le quadtree
    int donneNbEntites();

public:
    Quadtree(Rect cont);
    void effacer_fils();
    //renvoie si le noeud est une feuille
    bool est_feuille();
    //insere l'index de l'entite dans le quadtree
    void insert_id_entite(int indexTab);
    //recupere une liste de noeuds feuille qui contiennent le rectangle cible
    list<Quadtree> recupere_noeuds(list<Quadtree> noeuds_recup, Rect * rect);
    //recupere une liste d'index des entites succeptibles d'avoir une collision avec le rectangle
    void recupere_id_entites(list<int>& l_entites_recup, Rect * rect);
    //recupère la liste des index de toutes les entites à partir du noeud
    void recupIdToutesEntites(list<int>& l_entites_recup); 
    //Supprime l'id d'une entite du quadtree
    void supprime_id_entite(int index_ent);
};  

#endif