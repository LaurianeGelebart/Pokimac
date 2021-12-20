#include "consoleUtils.hpp"
#include "affichageTerrain.h"
#include "deplacement.h"
#include "menuDebut.h"

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>

#include <iostream>

 void initPlayer(Joueur *joueur);

int main() {

    int longueur = 0;
    int hauteur = 0;

    Joueur *joueur=new Joueur;

    // On affiche le menu
    menuDebut(&longueur, &hauteur);
    // On alloue le tableau 1D
    int NombreDeCases = longueur*hauteur ;
    int* tab = (int*)malloc(sizeof(int)*NombreDeCases);

    // On définie une position de départ au joueur et au pokimacs
    Position playerPos = {(rand() % hauteur + 1), (rand() % longueur + 1)};
    Position pokimacPos = {(rand() % hauteur + 1), (rand() % longueur + 1)};
    Position oldPos;

    affichageTerrain(hauteur, longueur, pokimacPos, playerPos);

    deplacement(&playerPos, &pokimacPos, &oldPos, hauteur, longueur) ;

	consoleUtils::clear();
	return 0;
}


    void initPlayer(Joueur *joueur){
        Inventaire *(joueur->inventaire ) = new Inventaire;
        Pokimac *(joueur->equipe) = new Pokimac;
        joueur->nom = "Sasha" ;
    }
