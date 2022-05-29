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
int current_niveau = 0;
//current_niveau comprends également les menus

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
    
    bool dim_ok, constantes_ok, decor_ok, perso_ok;
    dim_ok=false;
    constantes_ok=false;
    decor_ok=false;
    perso_ok=false;

    while (!feof(current_level)) {
        char c;
        fscanf(current_level, "%c", &c); 
        switch (c)
        {
        case '#':
            cin.ignore(256,'\n');
            //RETOURNER A LA LIGNE
        break;
        case 'D':
            {
                int l, h;
                fscanf(current_level, " %d %d", &l, &h);
                std::cout << l << " - " << h << std::endl;
                largeur_map = l;
                hauteur_map = h;
                if(!dim_ok) {
                    dim_ok=true;
                }
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
                if(!constantes_ok) {
                    constantes_ok=true;
                }
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
                liste_pers.push_back(Personnage(x, y, l, h, {r, g, b},a_h, a_v));
                if(!perso_ok) {
                    perso_ok=true;
                }
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
            //M <posX> <posY> <largeur> <hauteur> <rouge> <vert> <bleu> <vitesse_h> <vitesse_v>
            int x, y, w, h, v_h, v_v;
            float r, g, b;
            fscanf(current_level, " %d %d %d %d %f %f %f %d %d", &x, &y, &w, &h, &r, &g, &b, &v_h, &v_v);
            std::cout << x << " - " << y << " - " << w << " - " << h << " - " << r << " - " << g << " - " << b << " - " << v_h << " - " << v_v << std::endl;
            // std::cout << x << std::endl;
            
            liste_plat.push_back(Plateforme(x,y,w,h,{r,g,b},v_h,v_v));
            qtree.insert_id_entite(countEnt);
            countEnt++;
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
                liste_ent.push_back(make_shared<Decors>(x, y, w, h, Color3f{r, g, b}));
                qtree.insert_id_entite(countEnt);
                countEnt++;
                if(!decor_ok) {
                    decor_ok=true;
                }
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
                liste_ent.push_back(make_shared<Portail>(x, y, w, h, Color3f{r, g, b}));
                qtree.insert_id_entite(countEnt);
                countEnt++;
            }
            break;
        }
    }
    
    if (!dim_ok || !decor_ok || !perso_ok || !constantes_ok) {
        printf( "Erreur de chargement\n");
        //exit( -1 );
    }

    fclose(current_level);

    //exit(0); // PROVISOIRE POUR PAS QUE JOUER NIVEAU BOUCLE POUR L'INSTANT
    //Initialisation des entites

    //initialisation des plateformes
    
    //fscanf
}



//fonction accédant aux fonctionnalités du jeu
void jouer_niveau(){
    std::cout<<"dasn : "<<liste_pers[pers_select].est_dans_portail()<<std::endl;
    std::cout<<"tous dasn : "<<personnages_sont_dans_portails()<<std::endl;
    if (personnages_sont_dans_portails()==true) {
        current_niveau++;
        niveau_cpt++;
        std::cout <<"current : "<< current_niveau << std::endl;
        std::cout <<"niveau cpt : "<< niveau_cpt << std::endl;
        charger_niveau();
        return;
    }
    afficher_frame();
    if(NB_PLAT > 0){
            deplacer_plateformes();
        }
 
    deplacer_joueur();
    

    //Tant que tous les personnages ne sont pas dans les portails et que le joueur n'a pas choisi de quitter le jeu
    /*
    while (personnages_sont_dans_portails() == false && choix_joueur != QUITTER_JEU){
        afficher_frame(); //TO_DO 
        if(NB_PLAT > 0){
            deplacer_plateformes();
        }
        executer_choix_joueur(); //A finir
        deplacer_joueur();
    }
    */

    //std::cout << "portails:"<< personnages_sont_dans_portails() << std::endl;
    //std::cout << "choixjoueur:"<< choix_joueur << std::endl;

}

//fonction qui execute le niveau
void executer_niveau(int niveau_cpt){
    //qtree.initialiser_quadtree();
    charger_niveau();
    if (!liste_pers.empty()) {
        jouer_niveau();
    }
    //TODO
    //fonction liberer niveau pour delete les tableaux, liste plat et pers et cleart liste_ent, vider tout, clear quadtree
}

void liberer_niveau() {
    //TODO
    //fonction liberer niveau pour delete les tableaux, liste plat et pers et cleart liste_ent, vider tout, clear quadtree
    liste_ent.clear();
    delete[] &liste_pers;
    delete[] &liste_plat;
}
