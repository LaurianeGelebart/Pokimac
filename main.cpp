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
void initPokimac(Pokimac *pok);
Pokimac * initPokimacTerrain(int nombre, int hauteur, int longueur);

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

    /*Position playerPos = {4,4}; //test avec des positions fixes
    Position pokimacPos = {5,7};
    Position oldPos;*/

    Pokimac *pok1=new Pokimac; //premier pokemon dans l'equipe
    initPokimac(pok1); // Fonctionnel mais ne crée que pikachu
    //affichePokimac(pok1); //affiche infos pokimac

    string name = "Sacha" ;
    initPlayer(joueur, *pok1, name, playerPos); //corrigée par Lauriane, fonctionnel

    Pokimac *pokimacTerrain = initPokimacTerrain(15, hauteur, longueur); //Liste des pokimac du terrain

    cout << "force : " << pokimacTerrain[0].force ;
/*
    ConsoleUtils::clear();


    while ((joueur->nbPokimac == 15){ //Tant que le joueur n'a pas 15 pokimacs --> on a pas gagné le jeu
        affichageTerrain(hauteur, longueur, tab, &pokimacTerrain, &playerPos);
        deplacement(joueur, &pokimacTerrain, hauteur, longueur,tab);//à modifier pour qu'on lalance à chaque fois qu'on appuie sur une touche
        ConsoleUtils::clear();
    }
    free(tab); */
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
    joueur->nbPokimac = 1 ;
}

//Initialiser pokimac 1 joueur
void initPokimac(Pokimac *pok){
    pok->nom = "Pikachu";
    pok->espece = "électrique";
    pok->ascii = 25  ;
    Attaque attaque1 ;
    Attaque attaque2 ;
    pok->attaque1 = attaque1 ;
    pok->attaque2 = attaque2 ;
    pok->defense = 25 ;
    pok->endurance = 25 ;
    pok->force = 25 ;
    pok->pv = 100 ;
   // pok->position = pokimacPos ; Lui mettre une position hors du terrain il est déjà dans notre équipe
}

//Initialiser les pokimac du terrain
Pokimac * initPokimacTerrain(int nombre, int hauteur, int longueur){
    Pokimac *pokimacTerrain ;
    for (int i=0 ; i<=nombre ; i++){
        pokimacTerrain =new Pokimac[i];
        pokimacTerrain[i].nom = "McLuhan";
        pokimacTerrain[i].espece = "électrique";
        pokimacTerrain[i].ascii = i+1  ;
        cout << pokimacTerrain[i].ascii ;
        Attaque attaque1 ;
        Attaque attaque2 ;
        pokimacTerrain[i].attaque1 = attaque1 ;
        pokimacTerrain[i].attaque2 = attaque2 ;
        pokimacTerrain[i].defense = rand() % 100 + 1 ;
        pokimacTerrain[i].endurance = rand() % 100 + 1 ;
        pokimacTerrain[i].force = rand() % 100 + 1 ;
        pokimacTerrain[i].pv = 100 ;
        pokimacTerrain[i].position = {(rand() * ((hauteur-1) - 1) / RAND_MAX + 1 ), (rand() * ((longueur-1) - 1) / RAND_MAX + 1 )};
    }
    return pokimacTerrain ;
}

