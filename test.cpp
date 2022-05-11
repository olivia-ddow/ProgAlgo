#include "structs_gen.h"
#include "rectangle.h"
#include "entite.h"
#include "quadtree.h"
#include "var_globales.h"
#include <list>
#include <vector>
using namespace std;

void test(){
    liste_ent.push_back(Entite({0,0,512,10, COLOR3FNUL}));
    qtree.insert_id_entite(0);

    liste_ent.push_back(Decors({300,140,60,100, COLOR3FNUL}));
    qtree.insert_id_entite(1);

    liste_ent.push_back(Decors({110,360,30,50, COLOR3FNUL}));
    qtree.insert_id_entite(2);

    liste_ent.push_back(Decors({270,280,140,20, COLOR3FNUL}));
    qtree.insert_id_entite(3);

    liste_ent.push_back(Personnage({140,100,20,40, COLOR3FNUL}));
    qtree.insert_id_entite(4);

    liste_ent.push_back(Personnage({170,140,30,30, COLOR3FNUL}));
    qtree.insert_id_entite(5);

    liste_ent.push_back(Portail({170,180,30,40, COLOR3FNUL}));
    qtree.insert_id_entite(6);

    liste_ent.push_back(Portail({170,180,30,40, COLOR3FNUL}));
    qtree.insert_id_entite(7);

    liste_ent.push_back(Plateforme({100,140,35,20, COLOR3FNUL}));
    qtree.insert_id_entite(8);

    liste_ent.push_back(Portail({140,170,20,40, COLOR3FNUL}));
    qtree.insert_id_entite(9);


}