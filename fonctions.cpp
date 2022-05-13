#include "fonctions.h"
#include "quadtree.h"
#include "var_globales.h"
#include "structs_gen.h"

/*bool Quadtree::intersection_non_nulle(Rectangle r1, Rectangle r2){
    //si r1 est completemnt a gauche de r2 OU completement en dessous OU completement a droite OU completement audessus
    //+ negation du resultat si dessus ->donne indication s'il y a zone commune entre r1 et r2 même cote a cote
    return !(r1.getX() + r1.getWidth() < r2.getX() || r1.getY() + r1.getHeight() < r2.getY() || r1.getX() > r2.getX() + r2.getWidth() || r1.getY() > r2.getY() + r2.getHeight());
}*/
//Detection Collision
bool intersection_non_nulle(Rectangle r1, Rectangle r2){
    //si r1 est a gauche de r2 (ou à la limite respectivement gauche de r2) OU en dessous OU a droite OU au dessus
    //+ negation du resultat si dessus -> donne indication s'il y a zone commune entre r1 et r2 mais pas cote a cote
    return !(r1.getX() + r1.getWidth() <= r2.getX() || r1.getY() + r1.getHeight() <= r2.getY() || r1.getX() >= r2.getX() + r2.getWidth() || r1.getY() >= r2.getY() + r2.getHeight());
}

void deplacer_plateformes(){
    //on traite toutes les plateformes
    for (int i =0; i < NB_PLAT ; i++){
        //calcul de la nouvelle postion à partir de la vitesse
        liste_plat[i].PutXarrivee(liste_plat[i].getX() + liste_plat[i].GetVitesseH());
        liste_plat[i].PutYarrivee(liste_plat[i].getY() + liste_plat[i].GetVitesseV());
        //recuperation de la liste des entites scupectible de causer une collision
        list<int> liste_colli;
        liste_colli = qtree.recupIdToutesEntites(liste_colli);
        //on teste la collision avec chaque entite
        bool collision_arrivee = false;
        for (auto j: liste_colli){
            if (i != j){
                if (intersection_non_nulle(liste_plat[i], liste_plat[j])){
                    collision_arrivee = true;
                //si la vitesse horizontale n'est pas nulle
                    if (liste_plat[i].GetVitesseH() != 0){
                        if (liste_plat[i].GetVitesseH() < 0){
                            //Si il va a gauche et collision, on le positionne sur le bord droit du rect ou il y a collision
                            liste_plat[i].PutXarrivee(liste_plat[j].getX()+liste_plat[j].getWidth());
                        } else {
                            //Sinon il va a droite et on le positionne a gauche du rectangle a collision
                            liste_plat[i].PutXarrivee(liste_plat[j].getX()-liste_plat[i].getWidth());
                        }
                    }

                    //On fait pareil pour la vitesse verticale
                    if (liste_plat[i].GetVitesseV() != 0){
                        if (liste_plat[i].GetVitesseV() < 0){
                            //Si il va en bas et collision, on le positionne sur le bord haut du rect ou il y a collision
                            liste_plat[i].PutYarrivee(liste_plat[j].getY()+liste_plat[j].getHeight());
                        } else {
                            //Sinon il va en haut et on le positionne sur le bord bas du rectangle a collision
                            liste_plat[i].PutYarrivee(liste_plat[j].getY()-liste_plat[i].getHeight());
                        }
                    }
                    //on inverse la vitesse pour changer de direction
                    liste_plat[i].PutVitesseH(-liste_plat[i].GetVitesseH());
                    liste_plat[i].PutVitesseV(-liste_plat[i].GetVitesseV());
                    //on quitte la boucle
                    break;
                }
            }
        }

        ///////////////////////////
        if (!collision_arrivee){
            for (int j = 0; j < NB_PERS; j++){
                if (intersection_non_nulle(liste_plat[i], liste_pers[j])){
                //si la vitesse horizontale n'est pas nulle
                    if (liste_plat[i].GetVitesseH() != 0){
                        if (liste_plat[i].GetVitesseH() < 0){
                            //Si il va a gauche et collision, on le positionne sur le bord droit du rect ou il y a collision
                            liste_plat[i].PutXarrivee(liste_plat[j].getX()+liste_pers[j].getWidth());
                        } else {
                            //Sinon il va a droite et on le positionne a gauche du rectangle a collision
                            liste_plat[i].PutXarrivee(liste_plat[j].getX()-liste_pers[i].getWidth());
                        }
                    }

                    //On fait pareil pour la vitesse verticale
                    if (liste_plat[i].GetVitesseV() != 0){
                        if (liste_plat[i].GetVitesseV() < 0){
                            //Si il va en bas et collision, on le positionne sur le bord haut du rect ou il y a collision
                            liste_plat[i].PutYarrivee(liste_pers[j].getY()+liste_pers[j].getHeight());
                        } else {
                            //Sinon il va en haut et on le positionne sur le bord bas du rectangle a collision
                            liste_plat[i].PutYarrivee(liste_pers[j].getY()-liste_plat[i].getHeight());
                        }
                    }
                    //on inverse la vitesse pour changer de direction
                    liste_plat[i].PutVitesseH(-liste_plat[i].GetVitesseH());
                    liste_plat[i].PutVitesseV(-liste_plat[i].GetVitesseV());
                    //on quitte la boucle
                    break;
                }
            }
        }
        //liste_plat[i].putX(liste_plat[i].GetXarrivee());
        //liste_plat[i].putY(liste_plat[i].GetYarrivee());
    }
}