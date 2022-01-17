#include "consoleUtils.hpp"
#include "declarations.h"
#include "affichageTerrain.h"
#include "deplacement.h"
#include "menuDebut.h"
#include "afficheASCII.h"
#include "combat.h"


#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>
#include <typeinfo>
#include <Windows.h>
#include <unistd.h>

#include <iostream>

using namespace std;

//Prototypes des fonctions
void initPlayer(Joueur *joueur, Pokimac pok1, string name, Position playerPos);
void initPokimac(Pokimac *pok);
Pokimac * initPokimacTerrain(int nombre, int hauteur, int longueur);

int main() {

    int longueur = 0;
    int hauteur = 0;
    int nombrePokimac = 0 ;
    int Arret = 1;

    Joueur *joueur=new Joueur;

    // On affiche le menu
    menuDebut(&longueur, &hauteur, &nombrePokimac);
    // On alloue le tableau 1D
    int NombreDeCases = longueur*hauteur ;
    char* tab = (char*)malloc(sizeof(char)*NombreDeCases);

    srand(time(NULL)); //Initialiser le générateur de nombres aléatores

    // On définit une position de départ  au joueur et aux pokimacs (pas possible de spawner en dehors ou sur les murs de la grille
    Position playerPos = {(rand() * ((hauteur-1) - 1) / RAND_MAX + 1 ), (rand() * ((longueur-1) - 1) / RAND_MAX + 1 )};
    Position centerPos = {(rand() * ((hauteur-1) - 1) / RAND_MAX + 1 ), (rand() * ((longueur-1) - 1) / RAND_MAX + 1 )};

    Pokimac *pok1=new Pokimac; //premier pokemon dans l'equipe
    initPokimac(pok1); // Fonctionnel mais ne crée que pikachu
    //affichePokimac(pok1); //affiche infos pokimac

    string name = "Sacha" ;
    initPlayer(joueur, *pok1, name, playerPos); //Initialisation du joueur

    Pokimac *pokimacTerrain = initPokimacTerrain(nombrePokimac, hauteur, longueur); //Liste des pokimac du terrain

    cout << "force : " << pokimacTerrain[0].force ;

    ConsoleUtils::clear();


    affichageTerrain(hauteur, longueur, tab, pokimacTerrain, &playerPos, nombrePokimac, centerPos);

    while (joueur->nbPokimac <= nombrePokimac && Arret != 0){ //Tant que le joueur n'a pas 15 pokimacs --> on a pas gagné le jeu
        bool special = false;
        Position oldPos ;
        oldPos = joueur->position;
        int c = ConsoleUtils::getChar(&special); // attend le caractere special
        if(special) {
            deplacement(joueur, hauteur, longueur,tab, c);//à modifier pour qu'on lalance à chaque fois qu'on appuie sur une touche
        }

        if (joueur->position.x != oldPos.x || joueur->position.y != oldPos.y) {
            for (int i=0 ; i<nombrePokimac ; i++){
                if ((oldPos.x == pokimacTerrain[i].position.x) && (oldPos.y == pokimacTerrain[i].position.y) ){
                    ConsoleUtils::setCursorPos(oldPos.x, oldPos.y);
                    std::cout << "P" ; // Affiche pokimac
                }else if ((oldPos.x == centerPos.x) && (oldPos.y == centerPos.y) ){
                    ConsoleUtils::setCursorPos(oldPos.x, oldPos.y);
                    std::cout << "C" ; // Affiche centre pokimac
                }else {
                    ConsoleUtils::setCursorPos(oldPos.x, oldPos.y);
                    std::cout << tab[oldPos.y*longueur+oldPos.x]; // Affiche ce qu'il y avait à l'ancienne position du joueur --> Clean
                }
            }
            ConsoleUtils::setCursorPos(joueur->position.x, joueur->position.y);
            std::cout << "@";
		}
		for (int i=0 ; i<nombrePokimac ; i++){
            if ((joueur->position.x == pokimacTerrain[i].position.x) && (joueur->position.y == pokimacTerrain[i].position.y) ){ // Si même position qu'un pokimac
                Arret = combat(joueur, &pokimacTerrain[i], hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos);
                //cout << Arret <<endl;
            }
		}
		if ((joueur->position.x == centerPos.x) && (joueur->position.y == centerPos.y) ){ // Si même position que le centre
                // Fonction du centre
                for (int i=0;i<(joueur->nbPokimac);i++){
                    (joueur->equipe[i]).pv = 100; // soigne entierement les pokemon de l'equipe du joueur
                    joueur->inventaire.nbPokiball = 15;
                    joueur->inventaire.nbBaie = 10;
                }
            }

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
    joueur->nbPokimac = 1 ;
}

//Initialiser pokimac 1 joueur
void initPokimac(Pokimac *pok){
    pok->nom = "Pikachu";
    pok->espece = "électrique";
    pok->ascii = 1 ;
    Attaque attaque1 ;
    Attaque attaque2 ;
    pok->attaque1.nom = "Eclair";
    pok->attaque1.puissance = rand() % 100 + 1 ;
    pok->attaque2.nom = "Tonnerre" ;
    pok->attaque2.puissance = rand() % 100 + 1 ;
    pok->defense = 25 ;
    pok->endurance = 25 ;
    pok->force = 25 ;
    pok->pv = 100 ;
   // pok->position = pokimacPos ; Lui mettre une position hors du terrain il est déjà dans notre équipe
}

//Initialiser les pokimac du terrain
Pokimac * initPokimacTerrain(int nombre, int hauteur, int longueur){
    Pokimac *pokimacTerrain ;
    pokimacTerrain =new Pokimac[nombre];
    for (int i=0 ; i<nombre ; i++){
        pokimacTerrain[i].nom = "McLuhan";
        pokimacTerrain[i].espece = "électrique";
        pokimacTerrain[i].ascii = 4  ;
        Attaque attaque1 ;
        Attaque attaque2 ;
        pokimacTerrain[i].attaque1.nom = "Message";
        pokimacTerrain[i].attaque1.puissance = rand() % 100 + 1;
        pokimacTerrain[i].attaque2.nom = "Medium" ;
        pokimacTerrain[i].attaque2.puissance = rand() % 100 + 1;
        pokimacTerrain[i].defense = rand() % 100 + 1 ;
        pokimacTerrain[i].endurance = rand() % 100 + 1 ;
        pokimacTerrain[i].force = rand() % 100 + 1 ;
        pokimacTerrain[i].confiance = rand() % 100 + 1 ;
        pokimacTerrain[i].pv = 100 ;
        pokimacTerrain[i].position = {(rand() * ((hauteur-1) - 1) / RAND_MAX + 1 ), (rand() * ((longueur-1) - 1) / RAND_MAX + 1 )};
    }
    return pokimacTerrain ;
}

