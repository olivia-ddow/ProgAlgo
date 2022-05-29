#include "quadtree.h"
#include "entite.h"
#include "structs_gen.h"
#include "menu.h"
#include "var_globales.h"
#include "niveau_manager.h"
#include "fonctions.h"
#include "inter_joueur.h"
#include "fakesdlimage.h"
#include "gestion_frame.h"
#include "memory"

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


int largeur_map = 0;
int hauteur_map = 0;

int val_accel_g = 0;
int val_accel_f = 0;
int val_max_vitesse_h = 0;
int val_max_vitesse_v = 0;

int NB_PERS = 0;
int NB_PLAT = 0;
int NB_PORT = 0;
int NB_ENT = 0;


SDL_Event e;

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 1920;
static const unsigned int WINDOW_HEIGHT = 1080;
static const char WINDOW_TITLE[] = "Through the seasons";

/* Espace fenetre virtuelle */

static const float GL_VIEW_SIZE = 540;
//static const float GL_VIEW_SIZE = 1920;
/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

vector<shared_ptr<Entite>> liste_ent;
vector<Entite> liste_btn;
vector<Personnage> liste_pers;

vector<Plateforme> liste_plat;

Rect conteneur(0,0,1920,1080);
Quadtree qtree(conteneur);


float aspectRatio ;

void onWindowResized(unsigned int width, unsigned int height)
{ 
     aspectRatio = width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if( aspectRatio > 1) 
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio, 
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
    }
    else
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
        -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
    }
}


/* Objets cannoniques */
void drawOrigin() 
{
    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR,currentColor);

    glBegin(GL_LINES);

    glColor3f(1., 0., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 1.0 , 0.0);

    glColor3f(0., 1., 0.);
    glVertex2f( 0.0 , 0.0);
    glVertex2f( 0.0 , 1.0);

    glEnd();

    glColor3fv(currentColor);
}

void drawBTN(GLuint texture, int i){

        glBindTexture(GL_TEXTURE_2D, texture);
        liste_btn[i].draw(1);
        
}
/*
void drawMenu(GLuint texture){
    for(int i=0; i<4; i++){
            drawBTN(texture[i], i);
    }
}
*/

/*
void quitter(){
    loop = 0;
    for (int i=0; i<4; i++){
            SDL_FreeSurface(image[i]);
    }
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}*/
int main(int argc, char** argv) 
{
    //* Initialisation de la SDL */

    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        const char* error = SDL_GetError();
        fprintf(
            stderr, 
            "Erreur lors de l'intialisation de la SDL : %s\n", error);

        SDL_Quit();
        return EXIT_FAILURE;
    }
	//fenetre debut
    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */

    SDL_Window* window;
    {
        window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        if(NULL == window) 
        {
            const char* error = SDL_GetError();
            fprintf(
                stderr,
                "Erreur lors de la creation de la fenetre : %s\n", error);

            SDL_Quit();
            return EXIT_FAILURE;
        }
    }
    
    SDL_GLContext context;
    {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        context = SDL_GL_CreateContext(window);
    
        if(NULL == context) 
        {
            const char* error = SDL_GetError();
            fprintf(
                stderr,
                "Erreur lors de la creation du contexte OpenGL : %s\n", error);

            SDL_DestroyWindow(window);
            SDL_Quit();
            return EXIT_FAILURE;
        }
    }    
  
    onWindowResized(WINDOW_WIDTH, WINDOW_HEIGHT);

    //Textures Menu
    
    SDL_Surface *image[4];
    
    char chemin[250];
    for(int i = 0; i < 3; i++){

        sprintf(chemin,"../texture/menu-%d.png",i);

        image[i] = IMG_Load(chemin);

        if(image[i] != NULL){
        
            printf("l'image a chargé\n");
        }else{
            printf("l'image n'a pas chargé\n");
        }
    }
    
    image[3]= IMG_Load("../texture/fin-0.png");
    
    GLuint textures[4];
    glGenTextures(4,textures);

    for(int i = 0; i < 4; i++){

        glBindTexture(GL_TEXTURE_2D, textures[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[i]->w, image[i]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE,image[i]->pixels);
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);
    
    
    /* Boucle principale */
    int loop = 1;
    charger_niveau();
    int posJBase = liste_pers[pers_select].getY();
while(loop) 
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

        if(current_niveau==0 || current_niveau==4){
            glTranslatef((-GL_VIEW_SIZE / 2. * aspectRatio),(-GL_VIEW_SIZE / 2.), 0.0);
        }else {
            //glTranslatef(-liste_pers[pers_select].GetXarrivee()-(GL_VIEW_SIZE)+100 ,liste_pers[pers_select].getY()-(GL_VIEW_SIZE) ,0);
            glTranslatef(-liste_pers[pers_select].GetXarrivee()-(GL_VIEW_SIZE)+300 ,posJBase-liste_pers[pers_select].getY()-(GL_VIEW_SIZE) ,0);
        }
        
        
        /*
        while (niveau_cpt != NB_NIVEAUX_MAX && choix_joueur != QUITTER_JEU){
            executer_niveau(niveau_cpt);
        }*/
        
        glEnable(GL_TEXTURE_2D);
        //glBindTexture(GL_TEXTURE_2D, texture);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        

        
        /* Boucle traitant les evenements */
        SDL_Delay(25);
        while(SDL_PollEvent(&e)) 
        {
            liste_pers[pers_select].PutAccelerationH(0);
            liste_pers[pers_select].PutAccelerationV(0);
            /* L'utilisateur ferme la fenetre : */
			if(e.type == SDL_QUIT) 
			{
				//quitter();
                loop = 0;
                for (int i=0; i<4; i++){
                        SDL_FreeSurface(image[i]);
                }
                SDL_GL_DeleteContext(context);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return EXIT_SUCCESS;
				break;
			}
		
			if(	e.type == SDL_KEYDOWN 
				&& (e.key.keysym.sym == QUITTER_JEU || e.key.keysym.sym == SDLK_ESCAPE))
			{
				//quitter();
                loop = 0;
                for (int i=0; i<4; i++){
                        SDL_FreeSurface(image[i]);
                }
                SDL_GL_DeleteContext(context);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return EXIT_SUCCESS;
				break;
			}
          
            
            switch(e.type) 
            {
                case SDL_WINDOWEVENT:
                    switch (e.window.event) 
                    {
                        /* Redimensionnement fenetre */
                        case SDL_WINDOWEVENT_RESIZED:
                            onWindowResized(e.window.data1, e.window.data2);                
                            break;

                        default:
                            break; 
                    }
                    break;

                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
                    // Au clic gauche
                    if(e.button.button == SDL_BUTTON_LEFT){

                        if (current_niveau == 0){
                            //MenuCliquable();
                                if((e.button.x >= 680 && e.button.x <= 1240)&&(e.button.y >= 410 && e.button.y <= 530)){
                                    printf("Bravo tu commences le jeu ! clic en (%d, %d)\n", e.button.x, e.button.y);
                                    current_niveau++;
                                };
                                if((e.button.x >= 680 && e.button.x <= 1240)&&(e.button.y >= 570 && e.button.y <= 700)){
                                    printf("Tu quittes le jeu! clic en (%d, %d)\n", e.button.x, e.button.y);
                                    loop=0;
                                    for (int i=0; i<4; i++){
                                        SDL_FreeSurface(image[i]);
                                    }
                                    SDL_GL_DeleteContext(context);
                                    SDL_DestroyWindow(window);
                                    SDL_Quit();
                                    return EXIT_SUCCESS;
                                };
                                
                        }
                        if (current_niveau == 4){
                                if((e.button.x >= 680 && e.button.x <= 1240)&&(e.button.y >= 410 && e.button.y <= 530)){
                                    printf("Bravo tu recommences le jeu ! clic en (%d, %d)\n", e.button.x, e.button.y);
                                    current_niveau = 0;
                                    
                                    
                                };
                                if((e.button.x >= 680 && e.button.x <= 1240)&&(e.button.y >= 570 && e.button.y <= 700)){
                                    printf("Tu quittes le jeu! clic en (%d, %d)\n", e.button.x, e.button.y);
                                    loop=0;
                                    for (int i=0; i<4; i++){
                                        SDL_FreeSurface(image[i]);
                                    }
                                    SDL_GL_DeleteContext(context);
                                    SDL_DestroyWindow(window);
                                    SDL_Quit();
                                    return EXIT_SUCCESS;
                                };
                               
    

                        }



                    }
                     // Au clic droit
                    if(e.button.button == SDL_BUTTON_RIGHT){
                        
                    }

                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    break;               
                case SDL_MOUSEBUTTONDOWN:
                    if(e.button.button == SDL_BUTTON_LEFT){

                        if((e.button.x >= 680 && e.button.x <= 1240)&&(e.button.y >= 410 && e.button.y <= 530)){
                            printf("En train de cliquer commencer le jeu : clic en (%d, %d)\n", e.button.x, e.button.y);
                            drawBTN(textures[2], 1);
                        };
                        if((e.button.x >= 680 && e.button.x <= 1240)&&(e.button.y >= 570 && e.button.y <= 700)){
                            printf("En train de cliquer quitter le jeu le jeu! clic en (%d, %d)\n", e.button.x, e.button.y);
                            
                        };

                    }
                break;
              
                /* Touche clavier */
                case SDL_KEYDOWN:

                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
                    switch(e.key.keysym.sym)
                    {
                        case GAUCHE:
                            printf("gauche");
                            std::cout << "perso:" << pers_select <<std::endl;
                            liste_pers[pers_select].PutAccelerationH(- liste_pers[pers_select].GetValAccelH());    
                            std::cout <<liste_pers[pers_select].GetAccelerationH() << std::endl;
                            //vider buffer
                            while(SDL_PollEvent (&e));
                        
                        break;
                        case DROITE:
                            printf("droite");
                            liste_pers[pers_select].PutAccelerationH(liste_pers[pers_select].GetValAccelH());
                            //vider buffer
                            while(SDL_PollEvent (&e));
                        break;
                        case SAUT:
                            printf("saut");
                            liste_pers[pers_select].PutAccelerationV(liste_pers[pers_select].GetValAccelV());
                            //vider buffer
                            while(SDL_PollEvent (&e));
                        break;
                        case TAB:
                            liste_pers[pers_select].PutC(-0.2);
                            pers_select = changer_selection(pers_select);
                            liste_pers[pers_select].PutC(0.2);
                            printf("Tu changes de personnage");
                        break;

                        default:
                            break;
                    }

                break;
                    
                default:
                    break;
            }
        }
        
        //if on est sur le menu
        if (current_niveau == 0){
            //drawMenu(textures);
            menudebut();
            for(int i=0; i<3; i++){
                drawBTN(textures[i], i);
            }
            
        }

       if (current_niveau == 1 || current_niveau == 2 || current_niveau == 3 ) {
       // if (current_niveau == 1 || current_niveau == 2 ) {
            if (!liste_pers.empty()) {
                    jouer_niveau();
            }
        }
        
        if(current_niveau == 4){
            //page de fin
            
            menufin();
            drawBTN(textures[3], 3);

        }


        glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
        
        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapWindow(window);
        
        

        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        
        
        /* Si trop peu de temps s'est ecoule, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) 
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
        
        

    
    }

    /* Liberation des ressources associees a la SDL */ 
    //quitter();
    loop = 0;
    for (int i=0; i<5; i++){
            SDL_FreeSurface(image[i]);
    }
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
