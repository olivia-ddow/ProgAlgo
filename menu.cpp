#include "structs_gen.h"
#include "rectangle.h"
#include "entite.h"
#include "quadtree.h"
#include "var_globales.h"
#include "niveau_manager.h"
#include <list>
#include <vector>
#include "menu.h"

using namespace std;



void menudebut(){
    
    //menu debut
    liste_btn.push_back(Entite({0,0,1040,540, {0.1,0.4,0.9}}));
  
    liste_btn.push_back(Entite({370,250,300,70, {0.3,0.7,0.9}}));

    liste_btn.push_back(Entite({370,160,300,70, {0.5,0.7,0.9}}));


}
    
void menufin(){
//menu fin
    liste_btn.push_back(Entite({0,0,1040,540, {0.1,0.7,0.1}}));

}
