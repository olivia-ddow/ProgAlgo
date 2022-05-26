#include "gestion_frame.h"
#include "quadtree.h"
#include "entite.h"
#include "structs_gen.h"
#include "test.h"
#include "var_globales.h"
#include "niveau_manager.h"
#include "fonctions.h"
#include "inter_joueur.h"
#include "interf_graph.h"


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
#include <iostream>
using namespace std;

void afficher_frame() {
    //TODO NE PAS OUBLIER DE METTRE A JOUR LA POSITION COURANTE DES PERS ET PLATEFORMES A LA FIN DU TRAITEMENT
    //draw ici, dessin toute la carte
    //Puis camera, juste au noeud
    //parcours toutes les listes et je les dessines, entite, plateforme (si i ly a des plateforme on les dessins), liste personnage
    //liste_ent[i].draw(1);
    //quisuieje portail

    //DECORS et PORTAILS
    for(int i = 0; i < NB_ENT; i++){
        liste_ent[i].draw(0);
    }
    //PERSONNAGES
    for(int i = 0; i < NB_PERS; i++){
        liste_pers[i].draw(0);
    }
    //PLATEFORMES
    if(NB_PLAT > 0){
        for(int i = 0; i < NB_PLAT; i++){
        liste_ent[i].draw(0);
        }
    }
    

}