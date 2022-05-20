#include "inter_joueur.h"
#include "interf_graph.h"
#include "fonctions.h"
#include "var_globales.h"
using namespace std;

//on déclare CHOIX_JOUEUR à indéfini
TypeChoix choix_joueur = CHOIX_INDEFINI;

//Rectangle personnage selectionne
int pers_select = 0;

//execute le choix du joueur
void executer_choix_joueur(){
    
    choix_joueur = retourner_appui_touche(); //TODO

    //acceleration a NUL quand on appuie pas sur une touche de direction
    liste_pers[pers_select].PutAccelerationH(0);
    liste_pers[pers_select].PutAccelerationV(0);

    switch (choix_joueur){
    case GAUCHE:
        //on met l'acceleration horizontale à gauche
        liste_pers[pers_select].PutAccelerationH(- liste_pers[pers_select].GetValAccelH());
        break;

    case DROITE:
        //on met l'acceleration horizontale à droite
        liste_pers[pers_select].PutAccelerationH(liste_pers[pers_select].GetValAccelH());
        break;

    case SAUT:
        //on met l'acceleration verticale
        liste_pers[pers_select].PutAccelerationV(liste_pers[pers_select].GetValAccelV());
        break;
        
    case MENU:
        //TODO
        break;

    case QUITTER_JEU:
        //TODO
        break;

    default:
        break;
    }
}

//deplacements du joueur
void deplacer_joueur(){

    int var_tmp = 0;

    //on traite tous les personnages
    for (int i =0; i < NB_PERS ; i++){

        //Si les personnages ne sont pas dans leur portails on les déplace sinon ils ne bougent pas
        if (liste_pers[i].est_dans_portail() == false){
            /*******VITESSE HORIZONTALE*****/
            //calcul de la vitesse H avant frottement en fonction de l'acceleration horizontale 
            liste_pers[i].PutVitesseH(liste_pers[i].GetVitesseH() + liste_pers[i].GetAccelerationH());
            
            //calcul de la vitesse H en fonction des frottements et verif de la vitesse max
            if (liste_pers[i].GetVitesseH() < 0){
                //calcul de la vitesse H en fonction des frottements
                var_tmp = liste_pers[i].GetVitesseH() + val_accel_f;
                //Si la vitesse devient positive avec les frottements on la met à zero
                if (var_tmp > 0){
                    var_tmp = 0;
                }
                //si la vitesse calculee depasse la vitesse max on ramène à la valeur max
                if (var_tmp < -val_max_vitesse_h){
                    var_tmp = -val_max_vitesse_h;
                }
            } else if (liste_pers[i].GetVitesseH() > 0){
                //calcul de la vitesse H en fonction des frottements
                var_tmp = liste_pers[i].GetVitesseH() - val_accel_f;
                //Si la vitesse devient negative avec les frottements on la met à zero
                if (var_tmp < 0){
                    var_tmp = 0;
                }
                //si la vitesse calculee depasse la vitesse max on ramène à la valeur max
                if (var_tmp > val_max_vitesse_h){
                    var_tmp = val_max_vitesse_h;
                }
            }
            //Sinon si la vitesse est nulle on fait rien

            /*******VITESSE VERTICALE*****/
            //calcul de la vitesse V avant frottement en fonction de l'acceleration verticale et de la gravite
            liste_pers[i].PutVitesseV(liste_pers[i].GetVitesseV() + liste_pers[i].GetAccelerationV() - val_accel_g);
            
            //Si la vitesse est negative (on descend) et quel depasse la vitesse max
            if (liste_pers[i].GetVitesseV() < 0 && liste_pers[i].GetVitesseV() < -val_max_vitesse_v){
                //on la ramène à la valeur max
                liste_pers[i].PutVitesseV(-val_max_vitesse_v);

            //Sinon si la vitesse est positive et qu'elle est sup à la vitesse max
            } else if (liste_pers[i].GetVitesseV() > 0 && liste_pers[i].GetVitesseV() > val_max_vitesse_v){
                //on la ramène à la valeur max
                liste_pers[i].PutVitesseV(val_max_vitesse_v);
            }
            //Sinon si la vitesse est nulle on fait rien
                
            /***CALCUL DE LA NOUVELLE POSITION***/
            liste_pers[i].PutXarrivee(liste_pers[i].getX() + liste_pers[i].GetVitesseH());
            //SI le Personnage n'est pas sur la plateforme OU s'il saute alors on calcule sa nouvelle position verticale
            if (liste_pers[i].EstSurPlateforme() == false || liste_pers[i].GetVitesseV() > 0) { //VOIR si ca fonctionne sinon réfléchir 
                liste_pers[i].PutYarrivee(liste_pers[i].getY() + liste_pers[i].GetVitesseV());
            }


            /***CHECK COLLISION ENTITE STATIQ*****/
            //recuperation de la liste des entites susceptible de causer une collision
            list<int> liste_colli;
            liste_colli = qtree.recupere_id_entites(liste_colli, liste_pers[i]);
            //on teste la collision avec chaque entite
            for (auto j: liste_colli){
                //S'il ya une collision
                if (intersection_non_nulle(liste_pers[i].RendRectArrivee(), liste_ent[j])){
                    //On verifie si le rectangle avec qui il collisionne est SON portail
                    if (liste_ent[j].quisuisje() == PORTAIL && taille_rec_est_identique(liste_pers[i], liste_ent[j])){
                        //on change l'attribut du pers 'dans_portail' à vrai
                        liste_pers[i].PutDansPortail(true);
                        //On met les coordonnées du portail à celle du personnage
                        liste_pers[i].PutXarrivee(liste_ent[j].getX());
                        liste_pers[i].PutYarrivee(liste_ent[j].getY());                    
                    } else {
                        //si la vitesse horizontale n'est pas nulle
                        if (liste_pers[i].GetVitesseH() != 0){
                            if (liste_pers[i].GetVitesseH() < 0){
                                //Si il va a gauche et collision, on le positionne sur le bord droit du rect ou il y a collision
                                var_tmp = liste_ent[j].getX()+liste_ent[j].getWidth();
                                //cas ou le pers rencontre plrs objets
                                if (liste_pers[i].GetXarrivee() < var_tmp){
                                    liste_pers[i].PutXarrivee(var_tmp);
                                }
                            } else {
                                //Sinon il va a droite et on le positionne a gauche du rectangle a collision
                                var_tmp = liste_ent[j].getX()-liste_pers[i].getWidth();
                                //cas ou le pers rencontre plrs objets
                                if (liste_pers[i].GetXarrivee() > var_tmp){
                                    liste_pers[i].PutXarrivee(var_tmp);
                                }
                            }
                            //on met la vitesse à zéro pour que le pers s'arrête horizontalement
                            liste_pers[i].PutVitesseH(0);
                        }
                        //On fait pareil pour la vitesse verticale
                        if (liste_pers[i].GetVitesseV() != 0){
                            if (liste_pers[i].GetVitesseV() < 0){
                                //Si il va en bas et collision, on le positionne sur le bord haut du rect ou il y a collision
                                var_tmp = liste_ent[j].getY()+liste_ent[j].getHeight();
                                //cas ou le pers rencontre plrs objets
                                if (liste_pers[i].GetYarrivee() < var_tmp){
                                    liste_pers[i].PutYarrivee(var_tmp);
                                }
                                //seulement si on va en bas on se met à la vitess h 0 
                                liste_pers[i].PutVitesseH(0);
                            } else {
                                //Sinon il va en haut et on le positionne sur le bord bas du rectangle a collision
                                var_tmp = liste_ent[j].getY()-liste_pers[i].getHeight();
                                //cas ou le pers rencontre plrs objets
                                if (liste_pers[i].GetYarrivee() > var_tmp){
                                    liste_pers[i].PutYarrivee(var_tmp);
                                }
                            }
                            //on met la vitesse à zéro pour que le pers s'arrête verticalement et horizontalement
                            liste_pers[i].PutVitesseV(0);
                        }
                    }    
                }
            }
            
            /******CHECK COLLI AVEC AUTRES PERSONNAGES******/
            for (int j = 0; j < NB_PERS; j++){
                if (i != j){
                    //S'il ya une collision
                    if (intersection_non_nulle(liste_pers[i].RendRectArrivee(), liste_pers[j])){
                        //si la vitesse horizontale n'est pas nulle
                        if (liste_pers[i].GetVitesseH() != 0){
                            if (liste_pers[i].GetVitesseH() < 0){
                                //Si il va a gauche et collision, on le positionne sur le bord droit du rect ou il y a collision
                                liste_pers[i].PutXarrivee(liste_pers[j].getX()+liste_pers[j].getWidth());
                            } else {
                                //Sinon il va a droite et on le positionne a gauche du rectangle a collision
                                liste_pers[i].PutXarrivee(liste_pers[j].getX()-liste_pers[i].getWidth());
                            }
                            //on met la vitesse à zéro pour que le pers s'arrête horizontalement
                            liste_pers[i].PutVitesseH(0);
                        }
                        //On fait pareil pour la vitesse verticale
                        if (liste_pers[i].GetVitesseV() != 0){
                            if (liste_pers[i].GetVitesseV() < 0){
                                //Si il va en bas et collision, on le positionne sur le bord haut du rect ou il y a collision
                                var_tmp = liste_pers[j].getY()+liste_pers[j].getHeight();
                                //cas ou le pers rencontre plrs objets
                                if (liste_pers[i].GetYarrivee() < var_tmp){
                                    liste_pers[i].PutYarrivee(var_tmp);
                                }
                            } else {
                                //Sinon il va en haut et on le positionne sur le bord bas du rectangle a collision
                                var_tmp = liste_pers[j].getY()-liste_pers[i].getHeight();
                                //cas ou le pers rencontre plrs objets
                                if (liste_pers[i].GetYarrivee() > var_tmp){
                                    liste_pers[i].PutYarrivee(var_tmp);
                                }
                            }
                            //on met la vitesse à zéro pour que le pers s'arrête verticalement et horizontalement
                            liste_pers[i].PutVitesseV(0);
                            liste_pers[i].PutVitesseH(0);
                        }
                    }   
                }
            }


            /******CHECK COLLI AVEC PLATEFORMES******/
            for (int j = 0; j < NB_PLAT; j++){
                if (intersection_strict_non_nulle(liste_pers[i].RendRectArrivee(), liste_plat[j])){
                //si la vitesse horizontale n'est pas nulle
                    if (liste_pers[i].GetVitesseH() != 0){
                        if (liste_pers[i].GetVitesseH() < 0){
                            //Si il va a gauche et collision, on le positionne sur le bord droit du rect ou il y a collision
                            var_tmp = liste_plat[j].getX()+liste_plat[j].getWidth();
                            //cas ou le pers rencontre plrs objets
                            if (liste_pers[i].GetXarrivee() < var_tmp){
                                liste_pers[i].PutXarrivee(var_tmp);
                            }
                        } else {
                            //Sinon il va a droite et on le positionne a gauche du rectangle a collision
                            var_tmp = liste_plat[j].getX()-liste_pers[i].getWidth();
                            //cas ou le pers rencontre plrs objets
                            if (liste_pers[i].GetXarrivee() > var_tmp){
                                liste_pers[i].PutXarrivee(var_tmp);
                            }
                        }
                    }

                    //On fait pareil pour la vitesse verticale
                    if (liste_pers[i].GetVitesseV() != 0){
                        //si on descend;
                        if (liste_pers[i].GetVitesseV() < 0){
                            //Si il va en bas et collision, on le positionne sur le bord haut du rect ou il y a collision
                            var_tmp = liste_plat[j].getY()+liste_plat[j].getHeight();
                            //cas ou le pers rencontre plrs objets
                            if (liste_pers[i].GetYarrivee() < var_tmp){
                                liste_pers[i].PutYarrivee(var_tmp);
                            }
                            //on met la vitesse à zéro pour que le pers s'arrête verticalement et horizontalement
                            liste_pers[i].PutVitesseV(0);
                            liste_pers[i].PutVitesseH(0);
                            //On retient l'id de la plateforme sur laquelle est le personnage et inversement
                            liste_pers[i].PutIdPlateformeDessus(j);
                            liste_plat[j].PutIdPersSurPlateforme(i);
                        } else {
                            //Sinon il va en haut et on le positionne sur le bord bas du rectangle a collision
                            var_tmp = liste_plat[j].getY()-liste_pers[i].getHeight();
                            //cas ou le pers rencontre plrs objets
                            if (liste_pers[i].GetYarrivee() > var_tmp){
                                liste_pers[i].PutYarrivee(var_tmp);
                            }
                        }
                    }
                }
                //Si il est sur la plateforme et que l'index de la plateforme est celui noté dans l'attribut du pers ET que l'intersection est nulle
                if (liste_pers[i].EstSurPlateforme() && (liste_pers[i].GetIdPlateformeDessus() == j) && 
                                                        (intersection_non_nulle(liste_pers[i].RendRectArrivee(), liste_plat[j]) == false)){
                    //on dissocie le personnage de la plateforme 
                    liste_pers[i].AnnuleIdPlateformeDessus();
                    liste_plat[j].AnnuleIdPersDessus();
                }
            }

        }
        //liste_pers[i].putX(liste_pers[i].GetXarrivee());
        //liste_pers[i].putY(liste_pers[i].GetYarrivee()); //Faire dans les boucles des frames : pos.courante = posarrivee
    }
}