#include "consoleUtils.hpp"
#include "declarations.h"
#include "affichageTerrain.h"
#include "deplacement.h"
#include "menuDebut.h"
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>

#include <iostream>

using namespace std;

//Prototypes des fonctions
void initPlayer(Joueur *joueur, Pokimac pok1, string name, Position playerPos);
void initPokimac(Pokimac *pok);

int main() {

    int longueur = 0;
    int hauteur = 0;

    Joueur *joueur=new Joueur;

    // On affiche le menu
    menuDebut(&longueur, &hauteur);
    // On alloue le tableau 1D
    int NombreDeCases = longueur*hauteur ;
    int* tab = (int*)malloc(sizeof(int)*NombreDeCases);

    srand(time(NULL)); //Initialiser le générateur de nombres aléatores

    // On définie une position de départ au joueur et aux pokimacs
    Position playerPos = {(rand() % hauteur + 1), (rand() % longueur + 1)};
    Position pokimacPos = {(rand() % hauteur + 1), (rand() % longueur + 1)};
    Position oldPos;
    /*Position playerPos = {4,4}; //test avec des positions fixes
    Position pokimacPos = {5,7};
    Position oldPos;*/

    Pokimac pok1 ;
    string name = "Sasha" ;

    initPlayer(joueur, pok1, name, playerPos); //corrigée par Laurianne, fonctionnel
    cout << joueur->nom ;

    ConsoleUtils::clear();
   affichageTerrain(hauteur, longueur, pokimacPos, playerPos);

    deplacement(&playerPos, &pokimacPos, &oldPos, hauteur, longueur); //on n'arrive pas à se déplacer encore, les touches du clavier ne marche pas

	ConsoleUtils::clear();
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

//Initialiser pokimac
void initPokimac(Pokimac *pok){
//    pok->nom =;
}

