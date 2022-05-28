#include "structs_gen.h"
#include "rectangle.h"
#include "entite.h"
#include "quadtree.h"
#include "var_globales.h"
#include "niveau_manager.h"
#include <list>
#include <vector>
#include "test.h"

using namespace std;



void test(){
    
    liste_btn.push_back(Entite({0,0,1040,540, {0.1,0.4,0.9}}));
  
    liste_btn.push_back(Entite({370,250,300,70, {0.3,0.7,0.9}}));

    liste_btn.push_back(Entite({370,160,300,70, {0.5,0.7,0.9}}));

    liste_btn.push_back(Entite({370,70,300,70, {0.7,0.7,0.9}}));

    
    /*
    liste_ent.push_back(Entite({0,0,512,10, {0.3,0.4,0.9}}));
    qtree.insert_id_entite(0);

    liste_ent.push_back(Decors({300,140,60,100, {0.7,1.0,1.0}}));
    qtree.insert_id_entite(1);

    liste_ent.push_back(Decors({110,360,30,50, {0.3,0.1,0.9}}));
    qtree.insert_id_entite(2);

    liste_ent.push_back(Decors({270,280,140,20, {0.1,0.4,0.2}}));
    qtree.insert_id_entite(3);

    liste_ent.push_back(Personnage({140,100,20,40, {1.0,1.0,1.0}}));
    qtree.insert_id_entite(4);

    liste_ent.push_back(Personnage({170,140,30,30, {0.5,0.5,0.5}}));
    qtree.insert_id_entite(5);

    liste_ent.push_back(Portail({170,180,30,40, {0.1,0.1,0.9}}));
    qtree.insert_id_entite(6);

    liste_ent.push_back(Portail({170,180,30,40, {0.8,0.4,0.7}}));
    qtree.insert_id_entite(7);

    liste_ent.push_back(Plateforme({100,140,35,20, {0.3,0.8,0.1}}));
    qtree.insert_id_entite(8);

    liste_ent.push_back(Portail({140,170,20,40, COLOR3FNUL}));
    qtree.insert_id_entite(9);

    for(int i=0; i<liste_ent.size(); i++){
        liste_ent[i].draw();
    }*/

}