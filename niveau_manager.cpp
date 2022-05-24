#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include "niveau_manager.h"
#include "quadtree.h"
#include "var_globales.h"
#include "fonctions.h"
#include "inter_joueur.h"
#include "gestion_frame.h"

#include <iostream>

//Variable compteur de niveau initalisé à 0 (premier niveau)
int niveau_cpt = 0;

void charger_niveau(){
    //TO_DO
    //mettre les valeurs (fichier textes) des variables ici)
    /*
    FILE * current_level;
    char* result = (char*)"niveau"; 
    std::string tmp = std::to_string(niveau_cpt);
    char const *num_char = tmp.c_str();

    strcat( result, num_char );
    strcat( result, ".txt" );

    */
    std::string levelName = "niveau" + std::to_string(niveau_cpt) + ".txt";

    std::cout << levelName << std::endl;
    FILE * current_level = fopen (levelName.c_str(),"r");

    if ( current_level == NULL ) {
        printf( "Cannot open file %s\n");
        exit( -1 );
    }

    fprintf(current_level,"r");

    char *file_contents;
    int countEnt=0;
    
    while (!feof(current_level)) {
        char c;
        fscanf(current_level, "%c", &c); 
        switch (c)
        {
        case 'D':
            {
            int x, y;
            fscanf(current_level, " %d %d", &x, &y);
            std::cout << x << " - " << y << std::endl;
            }
            break;
        case 'A':
            break;
        case 'O':
            break;
        case 'P':
            break;
        case 'Q':
            break;
        case 'R':

            int x, y, w, h;
            float r, g, b;
            fscanf(current_level, " %d %d %d %d %f %f %f", &x, &y, &w, &h, &r, &g, &b);
            std::cout << x << " - " << y << " - " << w << " - " << h << " - " << r << " - " << g << " - " << b << std::endl;
            // std::cout << x << std::endl;
            liste_ent.push_back(Decors({x, y, w, h, {r, g, b}}));
          //  qtree.insert_id_entite(countEnt);
            countEnt++;
            break;
        case 'T':
            break;
        }
    }

    fclose(current_level);

    exit(0); // PROVISOIRE POUR PAS QUE JOUER NIVEAU BOUCLE POUR L'INSTANT
    //Initialisation des entites

    //initialisation des plateformes
    
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
