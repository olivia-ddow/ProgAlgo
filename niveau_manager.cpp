#include "niveau_manager.h"
#include "quadtree.h"
#include "var_globales.h"
#include "fonctions.h"
#include "inter_joueur.h"
#include "gestion_frame.h"

//Variable compteur de niveau initalisé à 0 (premier niveau)
int niveau_cpt = 0;

void charger_niveau(){
    //TO_DO
    //mettre les valeurs (fichier textes) des variables ici)

    //Initialisation des entites

    //initialisation des plateformes
    
    //exemple
    /*
    int x= 50; 
    int y=10;
    int l=40 ;
    int h=70; 
    Color3f c={0.9,0.2,0.7};
    for(int i=0; i<NB_PLAT; i++){
        liste_plat[i] = new Plateforme;
        liste_plat[i].x=x;

    }
    */
   liste_ent.push_back(Entite({0,0,512,10, {0.3,0.4,0.9}}));
    qtree.insert_id_entite(0);

    //fscanf
}

//fonction accédant aux fonctionnalités du jeu
void jouer_niveau(){
    //Tant que tous les personnages ne sont pas dans les portails et que le joueur n'a pas choisi de quitter le jeu
    while (personnages_sont_dans_portails() != false && choix_joueur != QUITTER_JEU){
        afficher_frame(); //TO_DO 
        deplacer_plateformes();
        executer_choix_joueur(); //A finir
        deplacer_joueur();
    }

    if (choix_joueur != QUITTER_JEU){
        niveau_cpt++;
    }
}

//fonction qui execute le niveau
void executer_niveau(int niveau_cpt){
    qtree.initialiser_quadtree();
    charger_niveau();
    jouer_niveau();
    //TODO
    //fonction liberer niveau pour delete les tableaux, liste plat et pers et cleart liste_ent, vider tout, clear quadtree
}
