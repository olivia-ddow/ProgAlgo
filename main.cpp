#include "quadtree.h"
#include "entite.h"
#include "structs_gen.h"
#include "test.cpp"
#include "var_globales.h"

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
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 600;
static const char WINDOW_TITLE[] = "TD03 Minimal";

/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 250.;

/* Subdivisions cercle */
static const int CIRCLE_SUBDIVS = 2<<5;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

vector<Entite> liste_ent;
Quadtree qtree;
    


void onWindowResized(unsigned int width, unsigned int height)
{ 
    float aspectRatio = width / (float) height;

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

/*
GLuint createFirstArmIDList(){

    GLuint id = glGenLists(1); 

    glNewList(id, GL_COMPILE);
        glPushMatrix();
            glScalef(20,20,0);
            drawCircle(1);
        glPopMatrix();

        glBegin(GL_QUADS);
            glVertex2f(60,10);
            glVertex2f(60,-10);
            glVertex2f(0,-20);
            glVertex2f(0,20);
        glEnd();

        glPushMatrix();
            glTranslatef(60,0,0);
            glScalef(10,10,0);
            drawCircle(1);
        glPopMatrix();
    glEndList();

    return id;
}
*/
/*
GLuint createSecondArmIDList(){

    GLuint id = glGenLists(1); 

    glNewList(id, GL_COMPILE);
        glPushMatrix();
            glScalef(10,10,0);
            drawSquare(1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(25,0,0);
            glScalef(46,6,0);
            drawSquare(1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(50,0,0);
            glScalef(10,10,0);
            drawSquare(1);
        glPopMatrix();
    glEndList();

    return id;
}

GLuint createThirdArmIDList(){

    GLuint id = glGenLists(1); 

    glNewList(id, GL_COMPILE);
        glPushMatrix();
            glScalef(6,6,0);
            drawSquare(1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(20,0,0);
            glScalef(40,4,0);
            drawSquare(1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(40,0,0);
            glScalef(4,4,0);
            drawCircle(1);
        glPopMatrix();
    glEndList();

    return id;

    
}
*/
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

  
    /* Boucle principale */
    int loop = 1;
    float alpha=45.0;
    float beta=-10.0;
    float gamma = 35.0;
    float vitesse=0.1;

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
                        beta+=5;
                    }
                     // Au clic droit
                    if(e.button.button == SDL_BUTTON_RIGHT){
                        beta-=5;
                    }

                    printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    break;
                
                

                /* Touche clavier */
                case SDL_KEYDOWN:
                    printf("touche pressee (code = %d)\n", e.key.keysym.sym);
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
        
        if(alpha<-45.0){
            vitesse=0.03;
        }
        if(alpha>45.0){
            vitesse=-0.03;
        }
        alpha+=vitesse*elapsedTime;
        

    
    }

    /* Liberation des ressources associees a la SDL */ 
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}
