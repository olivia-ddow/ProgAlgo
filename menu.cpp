
#include "menu.h"

using namespace std;

/*
void afficheTitre(){

}


//fonction qui affiche les options du menu avant le début du jeu
void afficheOptionsMenu(){

}

//fonction qui affiche les options du menu pendant la partie
void afficheOptionsMenuPendantPartie(){
    
}

//fonction qui affiche le menu pendant la partie
void MenuPendantPartie(T_ptjeu jeu){
    
    int choixMenuPP = 0;
    do{
        afficheOptionsMenuPendantPartie();
        cin >> choixMenuPP;
        choixMenuPP = verifier_entree_int_joueur(&choixMenuPP);

        switch(choixMenuPP){
            case MENU_JEU:  //continuer
            {
                cout << "vous continuez le jeu" <<endl;
            }
            break;
            break;
            case MENU_QUITJEU:  //quitter;
            {
                string q;
                do{
                    cout << "Etes vous certain de vouloir quitter la partie? Toute progression sera perdue. (O/N)";
                    cin >> q;
                    if(q=="O" || q=="o"){
                        system("cls");

                        cout << "Au revoir !" <<endl;
                        sleep(1000);
                        exit(0);
                    }
                    else if(q=="N" || q=="n"){
                        cout << "Vous continuez le jeu" <<endl;
                    }
                    else{
                        cout <<"Veuillez selectionner O ou N" <<endl;
                    }
                }while(q!="O" && q!="o" && q!="N" && q!="n");

            }
            break;
            default:
            {
                cout << "erreur: veuillez entrer 1,2 ou 3." <<endl;
            }
            break;
        }
    }while (choixMenuPP !=0 && choixMenuPP != MENU_QUITJEU && choixMenuPP != MENU_JEU);
}


//fonction qui affiche le menu d'avant partie
void MenuAvantPartie(dresseur *lejoueur)
{
    int choixMenu=0;
    do{
        afficheOptionsMenu();
        cin >> choixMenu;
        choixMenu = verifier_entree_int_joueur(&choixMenu);
        switch(choixMenu){
            case MENU_JEU:  //jouer;
            {
                system("cls");
                cout << "vous avez lance le jeu" <<endl;
            }
            break;
            case MENUAV_PROFIL:  //modifier profil;
            {
                system("cls");
                int choixProfil = 0;
                do{
                    cout << "1. Nom" <<endl;
                    cout << "2. Sexe" <<endl;
                    cin >> choixProfil;
                    verifier_entree_int_joueur(&choixProfil);
                    if(choixProfil == PROFIL_NOM){
                        system("cls");
                        cout<<endl;
                        cout << "   NOM DU DRESSEUR" <<endl<<endl;
                        choisirNomDresseur(lejoueur);
                    }
                    else if(choixProfil == PROFIL_SEXE){
                        system("cls");
                        cout<<endl;
                        cout << "   SEXE DU DRESSEUR" <<endl<<endl;
                        choisirSexeDresseur(lejoueur);
                    }
                    else{
                        cout << " Veuillez selectionner 1 ou 2"<< endl;

                    }
                }
                while(choixProfil != PROFIL_NOM && choixProfil != PROFIL_SEXE);
            }
            break;
            case MENUAV_REGLE:
            {
                system("cls");
                afficheRegles(lejoueur); //affiche les règles
            }

            break;
            case MENUAV_QUITJEU:  //quitter;
            {
                system("cls");
                cout << "Au revoir !" <<endl;
                sleep(1000);
                exit(0);
            }
            break;
            default:  // clear et réaffiche;
            {
                system("cls");
                cout << "erreur: veuillez entrer 1,2,3 ou 4." <<endl;
            }
            break;
        }
    }while (choixMenu !=0 && choixMenu != MENUAV_QUITJEU && choixMenu != MENU_JEU );
}


*/