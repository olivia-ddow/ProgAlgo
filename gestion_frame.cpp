#include "gestion_frame.h"
#include "quadtree.h"
#include "entite.h"
#include "structs_gen.h"
#include "menu.h"
#include "var_globales.h"
#include "niveau_manager.h"
#include "fonctions.h"
#include "inter_joueur.h"



#include <SDL2/SDL.h>
// use lodepng instead
// #include <SDL2/SDL_image.h>
#if defined(_WIN32)
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>

void afficher_frame() {
    //parcours toutes les listes et je les dessine, entite, plateforme (si i ly a des plateforme on les dessins), liste personnage

    //DECORS et PORTAILS
    for(int i = 0; i < NB_ENT; i++){
        if(liste_ent[i]->quisuisje() == PORTAIL){
            liste_ent[i]->draw(2);
        }else{
            liste_ent[i]->draw(0);
        }
    }

    //PERSONNAGES
    for(int i = 0; i < NB_PERS; i++){
        liste_pers[i].draw(0);
    }

    //PLATEFORMES
    if(NB_PLAT > 0){
        for(int i = 0; i < NB_PLAT; i++){
        liste_plat[i].draw(0);
        }
    }
    
}