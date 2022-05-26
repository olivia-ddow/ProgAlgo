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
   std::cout << niveau_cpt << std::endl;
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
        case '#':
            
            //RETOURNER A LA LIGNE
        break;
        case 'D':
            {
                int l, h;
                fscanf(current_level, " %d %d", &l, &h);
                std::cout << l << " - " << h << std::endl;
                largeur_map = l;
                hauteur_map = h;
            }
            break;
        case 'A':
            {
                int g, f, v_h, v_v;
                fscanf(current_level,"%d %d %d %d", &g, &f, &v_h, &v_v);
                val_accel_g = g;
                val_accel_f = f;
                val_max_vitesse_h = v_h;
                val_max_vitesse_v = v_v;
            }

            break;
        case 'O':
            {
                int x;
                fscanf(current_level,"%d", &x);
                NB_PERS = x;
            }
            
            break;
        case 'P':
            {
                int x, y, l, h, a_h, a_v;
                float r, g, b;
                fscanf(current_level, " %d %d %d %d %f %f %f %d %d", &x, &y, &l, &h, &r, &g, &b, &a_h, &a_v);
                liste_pers.push_back(Personnage({x, y, l, h, {r, g, b},a_h, a_v}));
            }
            
            break;

        case 'L':
            {
                int x;
                fscanf(current_level,"%d", &x);
                NB_PLAT = x;
            }
        
        break;

        //Plateforme
        case 'M':
        break;
 
        case 'Q':
            {
                int x;
                fscanf(current_level,"%d", &x);
                NB_ENT = x;
            }

        
            break;
        case 'R':
            {
                int x, y, w, h;
                float r, g, b;
                fscanf(current_level, " %d %d %d %d %f %f %f", &x, &y, &w, &h, &r, &g, &b);
                std::cout << x << " - " << y << " - " << w << " - " << h << " - " << r << " - " << g << " - " << b << std::endl;
                // std::cout << x << std::endl;
                liste_ent.push_back(Decors({x, y, w, h, {r, g, b}}));
                qtree.insert_id_entite(countEnt);
                countEnt++;
            }
            
            break;
        
        //PORTAILS (en stroke)
        case 'T':
            {
                int x, y, w, h;
                float r, g, b;
                fscanf(current_level, " %d %d %d %d %f %f %f", &x, &y, &w, &h, &r, &g, &b);
                std::cout << x << " - " << y << " - " << w << " - " << h << " - " << r << " - " << g << " - " << b << std::endl;
                // std::cout << x << std::endl;
                liste_ent.push_back(Portail({x, y, w, h, {r, g, b}}));
                qtree.insert_id_entite(countEnt);
                countEnt++;
            }
            break;
        }
    }

    fclose(current_level);

    //exit(0); // PROVISOIRE POUR PAS QUE JOUER NIVEAU BOUCLE POUR L'INSTANT
    //Initialisation des entites

    //initialisation des plateformes
    
    //fscanf
}

//fonction accédant aux fonctionnalités du jeu
void jouer_niveau(){
    //Tant que tous les personnages ne sont pas dans les portails et que le joueur n'a pas choisi de quitter le jeu
    while (personnages_sont_dans_portails() == false && choix_joueur != QUITTER_JEU){
        afficher_frame(); //TO_DO 
        if(NB_PLAT > 0){
            deplacer_plateformes();
        }
        executer_choix_joueur(); //A finir
        deplacer_joueur();
    }
    std::cout << "portails:"<< personnages_sont_dans_portails() << std::endl;
    std::cout << "choixjoueur:"<< choix_joueur << std::endl;
    if (choix_joueur != QUITTER_JEU){
        std::cout << "bruuuh" << std::endl;
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
