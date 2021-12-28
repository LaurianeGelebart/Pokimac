#include "consoleUtils.hpp"
#include "declarations.h"
#include "affichageTerrain.h"
#include "deplacement.h"
#include "menuDebut.h"
#include "afficheASCII.h"
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>
#include <typeinfo>

#include <iostream>

using namespace std;

//Prototypes des fonctions
void initPlayer(Joueur *joueur, Pokimac pok1, string name, Position playerPos);
void initPokimac(Pokimac *pok, Position pokimacPos);
void affichePokimac(Pokimac *pok);

int main() {

    int longueur = 0;
    int hauteur = 0;

    Joueur *joueur=new Joueur;

    // On affiche le menu
    menuDebut(&longueur, &hauteur);
    // On alloue le tableau 1D
    int NombreDeCases = longueur*hauteur ;
    char* tab = (char*)malloc(sizeof(char)*NombreDeCases);

    srand(time(NULL)); //Initialiser le générateur de nombres aléatores

    // On définit une position de départ  au joueur et aux pokimacs (pas possible de spawner en dehors ou sur les murs de la grille
    Position playerPos = {(rand() * ((hauteur-1) - 1) / RAND_MAX + 1 ), (rand() * ((longueur-1) - 1) / RAND_MAX + 1 )};
    Position pokimacPos = {(rand() * ((hauteur-1) - 1) / RAND_MAX + 1 ), (rand() * ((longueur-1) - 1) / RAND_MAX + 1 )};

    /*Position playerPos = {4,4}; //test avec des positions fixes
    Position pokimacPos = {5,7};
    Position oldPos;*/

    Pokimac *pok1=new Pokimac; //premier pokemon dans l'equipe
    initPokimac(pok1, pokimacPos); // Fonctionnel mais ne crée que pikachu
    affichePokimac(pok1); //affiche infos pokimac

    string name = "Sacha" ;
    initPlayer(joueur, *pok1, name, playerPos); //corrigée par Lauriane, fonctionnel


    //ConsoleUtils::clear();


    while (true){ //trouver comment sortir du programme


        //affichageTerrain(hauteur, longueur, tab, &pokimacPos, &playerPos);
        //deplacement(&playerPos, &pokimacPos, hauteur, longueur,tab);
        //ConsoleUtils::clear();
    }
    free(tab);
	return 0;
}

//Initialiser le joueur
void initPlayer(Joueur *joueur, Pokimac pok1, string name, Position playerPos){
    joueur->inventaire.nbBaie = 5 ;
    joueur->inventaire.nbPokiball = 10 ;
    joueur->nom = name ;
    joueur->position = playerPos ;
    joueur->equipe = new Pokimac[20];
    joueur->equipe[0] = pok1 ;
}

//Initialiser pokimac 1
void initPokimac(Pokimac *pok, Position pokimacPos){
    pok->nom = "Pikachu";
    pok->espece = "électrique";
    pok->ascii = 4  ;
    Attaque attaque1 ;
    Attaque attaque2 ;
    pok->attaque1 = attaque1 ;
    pok->attaque2 = attaque2 ;
    pok->defense = 25 ;
    pok->endurance = 25 ;
    pok->force = 25 ;
    pok->position = pokimacPos ;
}

void affichePokimac(Pokimac *pok){
    ConsoleUtils::clear();
    print_pokemon(pok->ascii) ;//ne fonctionne pas encore
    cout << pok->nom << endl ;
    cout << pok->espece << endl << endl ;
    cout << "Force : " << pok->force << endl ;
    cout << "Endurence : " << pok->endurance << endl ;
    cout << "Défense : " << pok->defense << endl ;
}


