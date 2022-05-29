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
//current_niveau comprend également les menus
int current_niveau = 0;


void charger_niveau(){

    //On récupère le fichier
    std::string levelName = "niveau" + std::to_string(niveau_cpt) + ".txt";

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

    //On parcourt le fichier en analysant la première lettre.
    // En fonction de la première lettre, on initialise nos valeurs et objets qui vont former notre carte. 
    while (!feof(current_level)) {
        char c;
        fscanf(current_level, "%c", &c); 
        switch (c)
        {
        case '#':
            cin.ignore(256,'\n');
            //RETOURNER A LA LIGNE
        break;

            //les dimensions
        case 'D':
            {
                int l, h;
                fscanf(current_level, " %d %d", &l, &h);
                largeur_map = l;
                hauteur_map = h;
                if(!dim_ok) {
                    dim_ok=true;
                }
            }
            break;
            //gravite, frottement, vitesse max personnages
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

            //nombre de personnages
        case 'O':
            {
                int x;
                fscanf(current_level,"%d", &x);
                NB_PERS = x;
            }
 
            break;

            //liste de personnages
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

            //nombre de plateformes
        case 'L':
            {
                int x;
                fscanf(current_level,"%d", &x);
                NB_PLAT = x;
            }
        
        break;

            //liste de plateformes
        case 'M':
            int x, y, w, h, v_h, v_v;
            float r, g, b;
            fscanf(current_level, " %d %d %d %d %f %f %f %d %d", &x, &y, &w, &h, &r, &g, &b, &v_h, &v_v);          
            liste_plat.push_back(Plateforme(x,y,w,h,{r,g,b},v_h,v_v));
        break;

            //nombre d'entités
        case 'Q':
            {
                int x;
                fscanf(current_level,"%d", &x);
                NB_ENT = x;
            }

            break;

            //liste des entités
        case 'R':
            
                int x1, y1, w1, h1;
                float r1, g1, b1;
                fscanf(current_level, " %d %d %d %d %f %f %f", &x1, &y1, &w1, &h1, &r1, &g1, &b1);
                liste_ent.push_back(make_shared<Decors>(x1, y1, w1, h1, Color3f{r1, g1, b1}));
                qtree.insert_id_entite(countEnt);
                countEnt++;
                if(!decor_ok) {
                    decor_ok=true;
                }
            
            
            break;
        
            //liste des portails
        case 'T':
            
                int x2, y2, w2, h2;
                float r2, g2, b2;
                fscanf(current_level, " %d %d %d %d %f %f %f", &x2, &y2, &w2, &h2, &r2, &g2, &b2);
                liste_ent.push_back(make_shared<Portail>(x2, y2, w2, h2, Color3f{r2, g2, b2}));
                qtree.insert_id_entite(countEnt);
                countEnt++;
            
            break;

            //nombre de portails
        case 'N':
            {
                int x;
                fscanf(current_level,"%d", &x);
                NB_PORT = x;
            }
            break;

        }
        
    }
    
    if (!dim_ok || !decor_ok || !perso_ok || !constantes_ok) {
        printf( "Erreur de chargement\n");
    }

    fclose(current_level);
}



//fonction accédant aux fonctionnalités du jeu
void jouer_niveau(){
    afficher_frame();
    //S'il y a des plateformes
    if(NB_PLAT > 0){
        deplacer_plateformes();
    }
    deplacer_joueur();
}


//fonction permettant de libérer la mémoire entre chaque niveau.
void liberer_niveau() {
    liste_ent.clear();
    liste_pers.clear();
    liste_plat.clear();
    qtree.effacer_fils();
}