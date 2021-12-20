 #ifndef DECLARATION.H
 #define DECLARATION.H

#include "declarations.h"
#include "consoleUtils.hpp"
#include "affichageTerrain.h"
#include "deplacement.h"
#include "menuDebut.h"

 #endif


#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>

#include <iostream>

using namespace std;


void initPlayer(Joueur *joueur, Pokimac pok1,  Position playerPos);
void initPlayer(Pokimac *pok);

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

    // On définie une position de départ au joueur et au pokimacs
    Position playerPos = {(rand() % hauteur + 1), (rand() % longueur + 1)};
    Position pokimacPos = {(rand() % hauteur + 1), (rand() % longueur + 1)};
    Position oldPos;

    Pokimac pok1 ;
    string name = "Sasha" ;

    initPlayer(joueur, pok1, playerPos);

    affichageTerrain(hauteur, longueur, pokimacPos, playerPos);

    deplacement(&playerPos, &pokimacPos, &oldPos, hauteur, longueur) ;

	consoleUtils::clear();
	return 0;
}

//Initialiser le joueur
void initPlayer(Joueur *joueur, Pokimac pok1,Position *playerPos){
    Inventaire *inventaireJ = new Inventaire;
    inventaireJ->nbBaie = 5 ;
    inventaireJ->nbPokiball = 10 ;
    joueur->inventaire = *inventaireJ ;
    joueur->equipe[1] = pok1 ;
    joueur->nom = "Sasha" ;
    joueur->position = *playerPos ;
}

//Initialiser pokimac
void initPlayer(Pokimac *pok){
    pok->nom =
}

