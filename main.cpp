#include "quadtree.h"
#include "entite.h"
#include "structs_gen.h"
#include "test.h"
#include "var_globales.h"
#include "fakesdlimage.h"

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <vector>
#include <iostream>
using namespace std;

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 1920;
static const unsigned int WINDOW_HEIGHT = 1080;
static const char WINDOW_TITLE[] = "Through the seasons";

/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 540;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

vector<Entite> liste_ent;
Quadtree qtree;

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

void drawSquare(int filled) 
{
    if(filled) 
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
    }
    else 
    {
        glBegin(GL_LINE_STRIP);
    }

    glVertex2f( 0.5 , -0.5);
    glVertex2f( 0.5 , 0.5);
    glVertex2f( -0.5 , 0.5);
    glVertex2f( -0.5 , -0.5);
    glVertex2f( 0.5 , -0.5);

    glEnd();
}

void drawBTN(GLuint texture, int i){

        glBindTexture(GL_TEXTURE_2D, texture);
        liste_ent[i].draw(1);
        
}



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
    for(int i = 0; i < 4; i++){

        // CHANGER LA MANIERE DE RECUP LES IMAGES, TROP LONG
        sprintf(chemin,"../texture/menu-%d.png",i);

        image[i] = IMG_Load(chemin);

        if(image[i] != NULL){
        
            printf("l'image a chargé\n");
        }else{
            printf("l'image n'a pas chargé\n");
        }
    }
    /*
    image[1]= IMG_Load("../texture/menu-1.png");
    image[2]= IMG_Load("../texture/menu-2.png");
    image[3]= IMG_Load("../texture/menu-3.png");
    image[4]= IMG_Load("../texture/menu-4.png");
    */
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

    /*
    GLuint firstArmID=createFirstArmIDList();
    GLuint secondArmID=createSecondArmIDList();
    GLuint thirdArmID=createThirdArmIDList();
    */
    std::cout << "Hello World" << std::endl;
    while(loop) 
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();
        
        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

        glTranslatef((-GL_VIEW_SIZE / 2. * aspectRatio),(-GL_VIEW_SIZE / 2.), 0.0);

        
        glEnable(GL_TEXTURE_2D);
        //glBindTexture(GL_TEXTURE_2D, texture);
        glEnable(GL_AUTO_NORMAL);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        test();
        
        for(int i=0; i<4; i++){
            drawBTN(textures[i], i);
        }
        
        //drawBTN(textures[1], 0);

        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapWindow(window);
        
        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e)) 
        {
            /* L'utilisateur ferme la fenetre : */
			if(e.type == SDL_QUIT) 
			{
				loop = 0;
				break;
			}
		
			if(	e.type == SDL_KEYDOWN 
				&& (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
			{
				loop = 0; 
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
                        /*
                        if((e.button.x >= 580 && e.button.x <= 870)&&(e.button.y >= 530 && e.button.y <= 720)){
                            printf("Bravo tu commences le jeu ! clic en (%d, %d)\n", e.button.x, e.button.y);
                        }else if((e.button.x >= 580 && e.button.x <= 870)&&(e.button.y >= 530 && e.button.y <= 720)){
                            printf("Bravo tu commences le jeu ! clic en (%d, %d)\n", e.button.x, e.button.y);
                        }*/
                        // Les Y sont inversés
                        if((e.button.x >= 680 && e.button.x <= 1240)&&(e.button.y >= 410 && e.button.y <= 530)){
                            printf("Bravo tu commences le jeu ! clic en (%d, %d)\n", e.button.x, e.button.y);

                        };
                        if((e.button.x >= 680 && e.button.x <= 1240)&&(e.button.y >= 570 && e.button.y <= 700)){
                            printf("Tu choisis ton niveau! clic en (%d, %d)\n", e.button.x, e.button.y);
                        };
                        if((e.button.x >= 680 && e.button.x <= 1240)&&(e.button.y >= 740 && e.button.y <= 870)){
                            printf("Tu quittes le jeu! clic en (%d, %d)\n", e.button.x, e.button.y);
                            for (int i=0; i<4; i++){
                                SDL_FreeSurface(image[i]);
                            }
                            SDL_GL_DeleteContext(context);
                            SDL_DestroyWindow(window);
                            SDL_Quit();
                            return EXIT_SUCCESS;
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
                            printf("En train de cliquer commencer clic en (%d, %d)\n", e.button.x, e.button.y);

                        };
                        if((e.button.x >= 680 && e.button.x <= 1240)&&(e.button.y >= 570 && e.button.y <= 700)){
                            printf("En train de cliquer choisis ton niveau! clic en (%d, %d)\n", e.button.x, e.button.y);
                        };
                        if((e.button.x >= 680 && e.button.x <= 1240)&&(e.button.y >= 740 && e.button.y <= 870)){
                            printf("En train de cliquer le jeu! clic en (%d, %d)\n", e.button.x, e.button.y);
                            
                        }
                    }
                //POUR CHANGER DE PERSO CE SERA UTILE
                case SDL_MOUSEWHEEL:

                    if(e.wheel.y >0){
                        printf("Tu changes de personnage");
                    }else if(e.wheel.y <0){
                         printf("Tu changes de personnage aussi");
                    }

                /* Touche clavier */
                case SDL_KEYDOWN:

                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
                    switch(e.key.keysym.sym)
                    {
                        //Quand on clique sur echap on exit
                        case 46:
                            for (int i=0; i<4; i++){
                                SDL_FreeSurface(image[i]);
                            }
                            SDL_GL_DeleteContext(context);
                            SDL_DestroyWindow(window);
                            SDL_Quit();
                            return EXIT_SUCCESS;
                        break;
                    }
                    break;
                    
                default:
                    break;
            }
        }

        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        
        
        /* Si trop peu de temps s'est ecoule, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS) 
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
        
        

    
    }

    /* Liberation des ressources associees a la SDL */ 
    for (int i=0; i<4; i++){
        SDL_FreeSurface(image[i]);
    }
    
    //SDL_DestroyTexture(textures[5]);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
