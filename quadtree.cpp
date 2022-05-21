#include "quadtree.h"
#include "var_globales.h"
#include "fonctions.h"

Quadtree::Quadtree(){
    //NORMAL QUE CE SOIT VIDE?
}

Quadtree::Quadtree(Rectangle cont){
   conteneur = cont;
}

//definit le conteneur du quadtree
void Quadtree::definir_rect(Rectangle cont){
    conteneur = cont;
}

void Quadtree::initialiser_quadtree(){
    effacer_fils();
    liste_index_entite.clear();
    conteneur = RECTNUL;
}

//efface les enfants du Quadtree
void Quadtree::effacer_fils() {
    for (int i = 0; i < 4; i++) {
        if (fils[i] != nullptr) {
            fils[i]->liste_index_entite.clear();
            fils[i]->effacer_fils();
            delete fils[i];
            fils[i]=nullptr;
        }
    }
}

//Separe le conteneur du noeud en 4 parties
void Quadtree::separer(){
    int demil = (int)(conteneur.getWidth() / 2);
    int demih = (int)(conteneur.getHeight() / 2);
    int x = (int)conteneur.getX();
    int y = (int)conteneur.getY();
    
    //supdroit
    fils[0] = new Quadtree(Rectangle(x + demil, y + demih, demil, demih));
    //supgauche
    fils[1] = new Quadtree(Rectangle(x, y + demih, demil, demih));
    //infdroit
    fils[2] = new Quadtree(Rectangle(x + demil, y, demil, demih));
    //infgauche
    fils[3] = new Quadtree(Rectangle(x, y, demil, demih));
}

//renvoie la partie du QuadTree dans lequel se trouve le rectangle, si le rectangle chevauche plusieurs parties retourne -1
int Quadtree::donnePartieQuad(Rectangle rect){
    int index = -1;
    int x_milieu = conteneur.getX() + (conteneur.getWidth() / 2);
    int y_milieu = conteneur.getY() + (conteneur.getHeight() / 2);
    
    // Object can completely fit within the top quadrants
    bool partie_haute = (rect.getY() > y_milieu && rect.getY() + rect.getHeight() > y_milieu);
    // Object can completely fit within the bottom quadrants
    bool partie_basse = (rect.getY() < y_milieu);
    
    bool partie_gauche = (rect.getX() < x_milieu && rect.getX() + rect.getWidth() < x_milieu);

    bool partie_droite = (rect.getX() > x_milieu);
    // Object can completely fit within the left quadrants
    if (partie_gauche) {
        if (partie_haute) {
            index = 1;
        }
        else if (partie_basse) {
            index = 3;
        }
    }
    // Object can completely fit within the right quadrants
    else if (partie_droite) {
        if (partie_haute) {
            index = 0;
        }
        else if (partie_basse) {
            index = 2;
        }
    }
    return index;
}

//renvoie si le noeud est une feuille
bool Quadtree::est_feuille(){
    if (fils[0] == nullptr){
        return true;
    }
    return false;
}

//insere l'index de l'entite dans le quadtree
void Quadtree::insert_id_entite(int indexTab){

    //Si le noeud est une feuille
    if (est_feuille()){
        //Si le nb d'elements dans la liste est inferieur au nb max d'objet, on ajoute l'index du rectangle cible dans la liste
        if (liste_index_entite.size() < NB_OBJ_MAX){
            liste_index_entite.push_back(indexTab);
        } else {
            //Si trop d'element, on coupe le noeud en 4 fils
            separer();
            //On replace les entites dans leurs sous noeuds respectifs
            for (int j = 0; j < 4; j++){
                for (auto i: liste_index_entite){
                    //on regarde dans quel(s) sous rectangle(s) il faut mettre l'element
                    if (intersection_non_nulle(liste_ent[i], fils[j]->conteneur)){
                        //On insere l'entite dans le fils s'il y a une intersection entre lui et le conteneur du sous noeud
                        fils[j]->insert_id_entite(i);
                    } 
                }
                if (intersection_non_nulle(liste_ent[indexTab], fils[j]->conteneur)){
                    //On insere la nouvelle entite dans le fils s'il y a une intersection entre lui et le conteneur du sous noeud
                    fils[j]->insert_id_entite(indexTab);
                } 
            }
            //on vide la liste des entites 
            liste_index_entite.clear();
            
        }
    //Si c'est pas une feuille
    } else {
        for (int j = 0; j < 4; j++){
            if (intersection_non_nulle(liste_ent[indexTab], fils[j]->conteneur)){
                //On insere la nouvelle entite dans le fils s'il y a une intersection entre lui et le conteneur du sous noeud
                fils[j]->insert_id_entite(indexTab);
            } 
        }
    }
}

//recupere une liste de noeuds feuille qui contiennent le rectangle cible
list<Quadtree> Quadtree::recupere_noeuds(list<Quadtree> l_noeuds_recup, Rectangle rect){
    if (est_feuille()){
        if (intersection_non_nulle(rect, conteneur)){
            l_noeuds_recup.push_back(*this);
        }
    } else {
        for (int i = 0; i < 4; i++){
            if (intersection_non_nulle(rect, fils[i]->conteneur)){
                fils[i]->recupere_noeuds(l_noeuds_recup, rect);
            }
        }
    }
    return l_noeuds_recup;
}

//recupère la liste des index de toutes les entites à partir du noeud
list<int> Quadtree::recupIdToutesEntites(list<int> l_id_entites){
    if (est_feuille()){
        for (auto j: liste_index_entite){
            l_id_entites.push_back(j);
        }
    } else {
        for (int i = 0; i < 4; i++){
            fils[i]->recupIdToutesEntites(l_id_entites);
        }
    }
    return l_id_entites;
}

//recupere une liste d'index des entites succeptibles d'avoir une collision avec le rectangle
list<int> Quadtree::recupere_id_entites(list<int> l_entites_recup, Rectangle rect){
    if (est_feuille()){
        if (intersection_non_nulle(rect, conteneur)){
            for (auto j: liste_index_entite){
                l_entites_recup.push_back(j);
            }
        }
    } else {
        for (int i = 0; i < 4; i++){
            if (intersection_non_nulle(rect, fils[i]->conteneur)){
                fils[i]->recupere_id_entites(l_entites_recup, rect);
            }
        }
    }
    return l_entites_recup;
}


//renvoie le nb d'entites
int Quadtree::donneNbEntites(){
    int cpt = 0;
    if (est_feuille()){
        cpt = liste_index_entite.size();
    } else {
        for (int i = 0; i < 4; i++){
            cpt += fils[i]->donneNbEntites();
        }
    }
    return cpt;
}

//Supprime l'id d'une entite du quadtree
void Quadtree::supprime_id_entite(int index_ent){
    if (est_feuille()){
        liste_index_entite.remove(index_ent);
    } else {
        for (int i = 0; i < 4; i++){
            fils[i]->supprime_id_entite(index_ent);
        }
        //Si le nombre d'entité est inférieur au nb d'objet max
        if (donneNbEntites() < NB_OBJ_MAX){
            list<int> liste_index;
            liste_index = recupIdToutesEntites(liste_index);
            //on deplace les index de liste_index a la fin de liste_index_entite et on vide liste_index
            liste_index_entite.splice(liste_index_entite.end(), liste_index);   
        }
    }
}