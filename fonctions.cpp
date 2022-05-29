#include "fonctions.h"
#include "quadtree.h"
#include "var_globales.h"
#include "structs_gen.h"
#include <iostream>
//Detection Collision
bool intersection_strict_non_nulle(Rect *r1, Rect *r2){
    //si r1 est completemnt a gauche de r2 OU completement en dessous OU completement a droite OU completement audessus
    //+ negation du resultat si dessus ->donne indication s'il y a zone commune entre r1 et r2 même cote a cote
    return !(r1->getX() + r1->getWidth() < r2->getX() || r1->getY() + r1->getHeight() < r2->getY() || r1->getX() > r2->getX() + r2->getWidth() || r1->getY() > r2->getY() + r2->getHeight());
}
//Detection Collision
bool intersection_non_nulle(Rect *r1, Rect *r2){
    //si r1 est a gauche de r2 (ou à la limite respectivement gauche de r2) OU en dessous OU a droite OU au dessus
    //+ negation du resultat si dessus -> donne indication s'il y a zone commune entre r1 et r2 mais pas cote a cote
    return !(r1->getX() + r1->getWidth() <= r2->getX() || r1->getY() + r1->getHeight() <= r2->getY() || r1->getX() >= r2->getX() + r2->getWidth() || r1->getY() >= r2->getY() + r2->getHeight());
}

//change le personnage selectionne
int changer_selection(int pers_selectionne){
    //On passe au personnage suivant dans la liste, si c'est le dernier on revient à 0
    int proch_pers = (pers_selectionne+1)%NB_PERS;
    while (liste_pers[proch_pers].est_dans_portail()){
        proch_pers = (proch_pers+1)%NB_PERS;
       
    }
    return proch_pers;
}

//Retourne si deux rectangles ont les memes dimensions
bool taille_rec_est_identique(Rect *rec1, Rect *rec2){
    return (rec1->getWidth()==rec2->getWidth() && rec1->getHeight()==rec2->getHeight());
}

//Retourne le nombre de personnages qui sont dans les portails
bool personnages_sont_dans_portails(){
    //on cree une variable qui compte les personnages qui sont dans des portails
    int cpt = 0;
    //on parcourt les personnages
    for (int i = 0; i < NB_PERS; i++){

     
            //si le personnage est dans son portail
            if (liste_pers[i].est_dans_portail()){
                std::cout << "cpt : " << cpt <<std::endl;
                //on incrémente le compteur
                cpt++;
            }
       
    }
    //on retourne si il ya tous les pers dans leur portail ou no
    std::cout << "cpt : " << cpt <<std::endl;
    std::cout << "NB_Pers : " << cpt <<std::endl;
    std::cout << "return " <<(cpt == NB_PERS )<<std::endl;
    return (cpt == NB_PERS);
}


//on teste la collision de la plateforme avec chaque entite
bool check_collision_plat_ent(bool inversion_vitesse, int i, list<int> liste_colli_plat){
    int var_tmp = 0;
    for (auto j: liste_colli_plat){
        Rect rectTemp = liste_plat[i].RendRectArrivee();
        if (intersection_non_nulle(&rectTemp, liste_ent[j].get())){
            //si la vitesse horizontale n'est pas nulle
            if (liste_plat[i].GetVitesseH() != 0){
                if (liste_plat[i].GetVitesseH() < 0){
                    //Si il va a gauche et collision, on le positionne sur le bord droit du rect ou il y a collision
                    var_tmp = liste_ent[j]->getX()+liste_ent[j]->getWidth();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_plat[i].GetXarrivee() < var_tmp){
                        liste_plat[i].PutXarrivee(var_tmp);
                    }                      
                } else {
                    //Sinon il va a droite et on le positionne a gauche du rectangle a collision
                    var_tmp = liste_ent[j]->getX()-liste_plat[i].getWidth();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_plat[i].GetXarrivee() > var_tmp){
                        liste_plat[i].PutXarrivee(var_tmp);
                    }
                }
            }

            //On fait pareil pour la vitesse verticale
            if (liste_plat[i].GetVitesseV() != 0){
                if (liste_plat[i].GetVitesseV() < 0){
                    //Si il va en bas et collision, on le positionne sur le bord haut du rect ou il y a collision
                    var_tmp = liste_ent[j]->getY()+liste_ent[j]->getHeight();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_plat[i].GetYarrivee() < var_tmp){
                        liste_plat[i].PutYarrivee(var_tmp);
                    }
                } else {
                    //Sinon il va en haut et on le positionne sur le bord bas du rectangle a collision
                    var_tmp = liste_ent[j]->getY()-liste_plat[i].getHeight();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_plat[i].GetYarrivee() > var_tmp){
                        liste_plat[i].PutYarrivee(var_tmp);
                    }
                }
            }
            //on inverse la vitesse pour changer de direction
            inversion_vitesse = true;
        }
    }
    return inversion_vitesse;
}

//on teste la collision du pers sur la plateforme avec chaque entite
bool check_collision_pers_sur_plat_ent(bool inversion_vitesse, int id_pers, int i, list<int> liste_colli_pers){
    int var_tmp = 0;
    for (auto j: liste_colli_pers){
        Rect rectTemp = liste_pers[id_pers].RendRectArrivee();
        if (intersection_non_nulle(&rectTemp,liste_ent[j].get())){
            //si la vitesse horizontale n'est pas nulle
            if (liste_pers[id_pers].GetVitesseH() != 0){
                if (liste_pers[id_pers].GetVitesseH() < 0){
                    //Si il va a gauche et collision, on le positionne sur le bord droit du rect ou il y a collision
                    var_tmp = liste_ent[j]->getX()+liste_ent[j]->getWidth();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_pers[id_pers].GetXarrivee() < var_tmp){
                        liste_pers[id_pers].PutXarrivee(var_tmp);
                    }                      
                } else {
                    //Sinon il va a droite et on le positionne a gauche du rectangle a collision
                    var_tmp = liste_ent[j]->getX()-liste_plat[i].getWidth();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_pers[id_pers].GetXarrivee() > var_tmp){
                        liste_pers[id_pers].PutXarrivee(var_tmp);
                    }
                }
            }

            //On fait pareil pour la vitesse verticale
            if (liste_pers[id_pers].GetVitesseV() != 0){
                if (liste_pers[id_pers].GetVitesseV() < 0){
                    //Si il va en bas et collision, on le positionne sur le bord haut du rect ou il y a collision
                    var_tmp = liste_ent[j]->getY()+liste_ent[j]->getHeight();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_pers[id_pers].GetYarrivee() < var_tmp){
                        liste_pers[id_pers].PutYarrivee(var_tmp);
                    }
                } else {
                    //Sinon il va en haut et on le positionne sur le bord bas du rectangle a collision
                    var_tmp = liste_ent[j]->getY()-liste_pers[id_pers].getHeight();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_pers[id_pers].GetYarrivee() > var_tmp){
                        liste_pers[id_pers].PutYarrivee(var_tmp);
                    }
                }
            }
            //on inverse la vitesse pour changer de direction
            inversion_vitesse = true;                   
        }
    }
    return inversion_vitesse;
}

//Check des collisions de la plateforme avec les personnages
bool check_collision_plat_pers(bool inversion_vitesse, int i){
    int var_tmp = 0;
    for (int j = 0; j < NB_PERS; j++){
        Rect rectTemp = liste_plat[i].RendRectArrivee();
        if (intersection_non_nulle(&rectTemp,&liste_pers[j])){
        //si la vitesse horizontale n'est pas nulle
            if (liste_plat[i].GetVitesseH() != 0){
                if (liste_plat[i].GetVitesseH() < 0){
                    //Si il va a gauche et collision, on le positionne sur le bord droit du rect ou il y a collision
                    var_tmp = liste_pers[j].getX()+liste_pers[j].getWidth();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_plat[i].GetXarrivee() < var_tmp){
                        liste_plat[i].PutXarrivee(var_tmp);
                    }
                } else {
                    //Sinon il va a droite et on le positionne a gauche du rectangle a collision
                    var_tmp = liste_pers[j].getX()-liste_plat[i].getWidth();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_plat[i].GetXarrivee() > var_tmp){
                        liste_plat[i].PutXarrivee(var_tmp);
                    }
                }
            }

            //On fait pareil pour la vitesse verticale
            if (liste_plat[i].GetVitesseV() != 0){
                if (liste_plat[i].GetVitesseV() < 0){
                    //Si il va en bas et collision, on le positionne sur le bord haut du rect ou il y a collision
                    var_tmp = liste_pers[j].getY()+liste_pers[j].getHeight();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_plat[i].GetYarrivee() < var_tmp){
                        liste_plat[i].PutYarrivee(var_tmp);
                    }
                } else {
                    //Sinon il va en haut et on le positionne sur le bord bas du rectangle a collision
                    var_tmp = liste_pers[j].getY()-liste_plat[i].getHeight();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_plat[i].GetYarrivee() > var_tmp){
                        liste_plat[i].PutYarrivee(var_tmp);
                    }
                }
            }
            //on inverse la vitesse pour changer de direction
            inversion_vitesse = true;
        }
    }
    return inversion_vitesse;
}

//on teste la collision du pers sur la plateforme avec chaque pers
bool check_collision_pers_sur_plat_pers(bool inversion_vitesse, int id_pers, int i){
    int var_tmp = 0;
    for (int j = 0; j < NB_PERS; j++){
        //Si les personnages sont différents et qu'il y a une intersection
        Rect rectTemp = liste_pers[id_pers].RendRectArrivee();
        if (id_pers != j && intersection_non_nulle(&rectTemp, &liste_pers[j])){
        //si la vitesse horizontale n'est pas nulle
            if (liste_pers[id_pers].GetVitesseH() != 0){
                if (liste_pers[id_pers].GetVitesseH() < 0){
                    //Si il va a gauche et collision, on le positionne sur le bord droit du rect ou il y a collision
                    var_tmp = liste_pers[j].getX()+liste_pers[j].getWidth();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_pers[id_pers].GetXarrivee() < var_tmp){
                        liste_pers[id_pers].PutXarrivee(var_tmp);
                    }
                } else {
                    //Sinon il va a droite et on le positionne a gauche du rectangle a collision
                    var_tmp = liste_pers[j].getX()-liste_plat[i].getWidth();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_pers[id_pers].GetXarrivee() > var_tmp){
                        liste_pers[id_pers].PutXarrivee(var_tmp);
                    }
                }
            }

            //On fait pareil pour la vitesse verticale
            if (liste_pers[id_pers].GetVitesseV() != 0){
                if (liste_pers[id_pers].GetVitesseV() < 0){
                    //Si il va en bas et collision, on le positionne sur le bord haut du rect ou il y a collision
                    var_tmp = liste_pers[j].getY()+liste_pers[j].getHeight();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_pers[id_pers].GetYarrivee() < var_tmp){
                        liste_pers[id_pers].PutYarrivee(var_tmp);
                    }
                } else {
                    //Sinon il va en haut et on le positionne sur le bord bas du rectangle a collision
                    var_tmp = liste_pers[j].getY()-liste_pers[id_pers].getHeight();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_pers[id_pers].GetYarrivee() > var_tmp){
                        liste_pers[id_pers].PutYarrivee(var_tmp);
                    }
                }
            }
            //on inverse la vitesse pour changer de direction
            inversion_vitesse = true;
        }
    }
    return inversion_vitesse;
}

//Check collision entre plateformes
bool check_collision_plat_plat(bool inversion_vitesse, int i){
    int var_tmp = 0;
    for (int j = 0; j < NB_PLAT; j++){
        Rect rectTemp = liste_plat[i].RendRectArrivee();
        if (i != j && intersection_non_nulle(&rectTemp, &liste_plat[j])){
        //si la vitesse horizontale n'est pas nulle
            if (liste_plat[i].GetVitesseH() != 0){
                if (liste_plat[i].GetVitesseH() < 0){
                    //Si il va a gauche et collision, on le positionne sur le bord droit du rect ou il y a collision
                    var_tmp = liste_plat[j].getX()+liste_plat[j].getWidth();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_plat[i].GetXarrivee() < var_tmp){
                        liste_plat[i].PutXarrivee(var_tmp);
                    }
                } else {
                    //Sinon il va a droite et on le positionne a gauche du rectangle a collision
                    var_tmp = liste_plat[j].getX()-liste_plat[i].getWidth();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_plat[i].GetXarrivee() > var_tmp){
                        liste_plat[i].PutXarrivee(var_tmp);
                    }
                }
            }

            //On fait pareil pour la vitesse verticale
            if (liste_plat[i].GetVitesseV() != 0){
                if (liste_plat[i].GetVitesseV() < 0){
                    //Si il va en bas et collision, on le positionne sur le bord haut du rect ou il y a collision
                    var_tmp = liste_plat[j].getY()+liste_plat[j].getHeight();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_plat[i].GetYarrivee() < var_tmp){
                        liste_plat[i].PutYarrivee(var_tmp);
                    }
                } else {
                    //Sinon il va en haut et on le positionne sur le bord bas du rectangle a collision
                    var_tmp = liste_plat[j].getY()-liste_plat[i].getHeight();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_plat[i].GetYarrivee() > var_tmp){
                        liste_plat[i].PutYarrivee(var_tmp);
                    }
                }
            }
            //on inverse la vitesse pour changer de direction
            inversion_vitesse = true;
        }
    }
    return inversion_vitesse;
}

//on teste la collision du pers sur la plateforme avec chaque plateforme
bool check_collision_pers_sur_plat_plat(bool inversion_vitesse, int id_pers){
    int var_tmp = 0;
    for (int j = 0; j < NB_PLAT; j++){
        Rect rectTemp = liste_pers[id_pers].RendRectArrivee();
        if (intersection_non_nulle(&rectTemp, &liste_plat[j])){
        //si la vitesse horizontale n'est pas nulle
            if (liste_pers[id_pers].GetVitesseH() != 0){
                if (liste_pers[id_pers].GetVitesseH() < 0){
                    //Si il va a gauche et collision, on le positionne sur le bord droit du rect ou il y a collision
                    var_tmp = liste_plat[j].getX()+liste_plat[j].getWidth();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_pers[id_pers].GetXarrivee() < var_tmp){
                        liste_pers[id_pers].PutXarrivee(var_tmp);
                    }
                } else {
                    //Sinon il va a droite et on le positionne a gauche du rectangle a collision
                    var_tmp = liste_plat[j].getX() - liste_pers[id_pers].getWidth();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_pers[id_pers].GetXarrivee() > var_tmp){
                        liste_pers[id_pers].PutXarrivee(var_tmp);
                    }
                }
            }

            //On fait pareil pour la vitesse verticale
            if (liste_pers[id_pers].GetVitesseV() != 0){
                if (liste_pers[id_pers].GetVitesseV() < 0){
                    //Si il va en bas et collision, on le positionne sur le bord haut du rect ou il y a collision
                    var_tmp = liste_plat[j].getY() + liste_plat[j].getHeight();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_pers[id_pers].GetYarrivee() < var_tmp){
                        liste_pers[id_pers].PutYarrivee(var_tmp);
                    }
                } else {
                    //Sinon il va en haut et on le positionne sur le bord bas du rectangle a collision
                    var_tmp = liste_plat[j].getY() - liste_pers[id_pers].getHeight();
                    //cas ou la plateforme rencontre plrs objets
                    if (liste_pers[id_pers].GetYarrivee() > var_tmp){
                        liste_pers[id_pers].PutYarrivee(var_tmp);
                    }
                }
            }
            //on inverse la vitesse pour changer de direction
            inversion_vitesse = true;
        }
    }
    return inversion_vitesse;
}


//calcul du delta entre la position d'arrivee et la pos courante de la plateforme 
//et du delta entre la position d'arrivee et la pos courante du pers uniquement si le pers est sur plateforme
void calcule_delta_pers_et_plateforme(int i, int id_pers){
    int delta_x_plat = 0;
    int delta_y_plat = 0;
    int delta_x_pers = 0;
    int delta_y_pers = 0;

    if (liste_plat[i].PersEstSurPlateforme()){
        delta_x_plat = liste_plat[i].GetXarrivee() - liste_plat[i].getX();
        delta_y_plat = liste_plat[i].GetYarrivee() - liste_plat[i].getY(); 
        delta_x_pers = liste_pers[id_pers].GetXarrivee() - liste_pers[id_pers].getX();
        delta_y_pers = liste_pers[id_pers].GetYarrivee() - liste_pers[id_pers].getY();

        //Si il est inferieur a 0 la plat va a gauche donc il faut prendre le plus grand delta entre la plat et le pers
        if (delta_x_plat < 0){
            if (delta_x_plat < delta_x_pers){
                liste_plat[i].PutXarrivee(liste_plat[i].getX() + delta_x_pers);
                liste_pers[id_pers].PutXarrivee(liste_pers[id_pers].getX() + delta_x_pers);
            } else {
                liste_plat[i].PutXarrivee(liste_plat[i].getX() + delta_x_plat);
                liste_pers[id_pers].PutXarrivee(liste_pers[id_pers].getX() + delta_x_plat);
            }
        } else {
            //Si il est sup a 0 la plat va a droite donc il faut prendre le plus petit delta entre la plat et le pers
            if (delta_x_plat > delta_x_pers){
                liste_plat[i].PutXarrivee(liste_plat[i].getX() + delta_x_pers);
                liste_pers[id_pers].PutXarrivee(liste_pers[id_pers].getX() + delta_x_pers);
            } else {
                liste_plat[i].PutXarrivee(liste_plat[i].getX() + delta_x_plat);
                liste_pers[id_pers].PutXarrivee(liste_pers[id_pers].getX() + delta_x_plat);
            }
        }
        if (delta_y_plat < 0){
            if (delta_y_plat < delta_y_pers){
                liste_plat[i].PutYarrivee(liste_plat[i].getY() + delta_y_pers);
                liste_pers[id_pers].PutYarrivee(liste_pers[id_pers].getY() + delta_y_pers);
            } else {
                liste_plat[i].PutYarrivee(liste_plat[i].getY() + delta_y_plat);
                liste_pers[id_pers].PutYarrivee(liste_pers[id_pers].getY() + delta_y_plat);
            }
        } else {
            if (delta_y_plat > delta_y_pers){
                liste_plat[i].PutYarrivee(liste_plat[i].getY() + delta_y_pers);
                liste_pers[id_pers].PutYarrivee(liste_pers[id_pers].getY() + delta_y_pers);
            } else {
                liste_plat[i].PutYarrivee(liste_plat[i].getY() + delta_y_plat);
                liste_pers[id_pers].PutYarrivee(liste_pers[id_pers].getY() + delta_y_plat);
            }
        }

        liste_pers[id_pers].putX(liste_pers[id_pers].GetXarrivee()); 
        liste_pers[id_pers].putY(liste_pers[id_pers].GetYarrivee());
    }
}
//deplacements des plateformes
void deplacer_plateformes(){

    bool inversion_vitesse = false;
    int id_pers = -1;
    list<int> liste_colli_plat;
    list<int> liste_colli_pers;
    
    //on traite toutes les plateformes
    for (int i =0; i < NB_PLAT ; i++){
        //calcul de la nouvelle position à partir de la vitesse
        liste_plat[i].PutXarrivee(liste_plat[i].getX() + liste_plat[i].GetVitesseH());
        liste_plat[i].PutYarrivee(liste_plat[i].getY() + liste_plat[i].GetVitesseV());
        
        //recuperation de la liste des entites susceptibles de causer une collision
        Rect rectTemp = liste_plat[i].RendRectArrivee();
        qtree.recupere_id_entites(liste_colli_plat, &rectTemp);

        //on teste la collision de la plateforme avec chaque entite
        inversion_vitesse = check_collision_plat_ent(inversion_vitesse, i, liste_colli_plat);
        

        //S'il y a un pers sur la plateforme
        if (liste_plat[i].PersEstSurPlateforme()){
            //on recupère l'id du pers
            id_pers = liste_plat[i].GetIdPersSurPlateforme();

            //calcul de la nouvelle position du personnnage à partir de la vitesse de la plateforme
            liste_pers[id_pers].PutXarrivee(liste_pers[id_pers].getX() + liste_plat[i].GetVitesseH());
            liste_pers[id_pers].PutYarrivee(liste_pers[id_pers].getY() + liste_plat[i].GetVitesseV());

            //on recupère la liste des ids des entités susceptibles d'avoir une collision avec le pers
            Rect rectTemp = liste_pers[id_pers].RendRectArrivee();
            qtree.recupere_id_entites(liste_colli_pers, &rectTemp);

            //on teste la collision du pers sur la plateforme avec chaque entite
            inversion_vitesse = check_collision_pers_sur_plat_ent(inversion_vitesse, id_pers, i, liste_colli_pers);            
        }

        ////////Check des collisions de la plateforme avec les personnages
        inversion_vitesse = check_collision_plat_pers(inversion_vitesse, i);
        

        //on teste la collision du pers sur la plateforme avec chaque pers
        inversion_vitesse = check_collision_pers_sur_plat_pers(inversion_vitesse, id_pers, i);
        

        ////Check collision entre plateformes
        inversion_vitesse = check_collision_plat_plat(inversion_vitesse, i);


        //on teste la collision du pers sur la plateforme avec chaque plateforme
        inversion_vitesse = check_collision_pers_sur_plat_plat(inversion_vitesse, id_pers);
        

        //Si il ya une inversion de vitesse, on inverse la vitesse pour changer de direction
        if(inversion_vitesse){
            liste_plat[i].PutVitesseH(-liste_plat[i].GetVitesseH());
            liste_plat[i].PutVitesseV(-liste_plat[i].GetVitesseV());
        }

        //calcul du delta entre la position d'arrivee et la pos courante de la plateforme 
        //et du delta entre la position d'arrivee et la pos courante du pers uniquement si le pers est sur plateforme
        calcule_delta_pers_et_plateforme(i, id_pers);

        liste_plat[i].putX(liste_plat[i].GetXarrivee());
        liste_plat[i].putY(liste_plat[i].GetYarrivee());

    }
}