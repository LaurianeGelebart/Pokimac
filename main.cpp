#include "consoleUtils.hpp"
#include "declarations.h"
#include "affichageTerrain.h"
#include "deplacement.h"
#include "menuDebut.h"
#include "afficheASCII.h"
#include "afficheASCII.h"


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
int combat(Joueur *joueur, Pokimac *pokRencontre, int hauteur, int longueur, char* tab, Pokimac* pokimacTerrain, int nombrePokimac) ;
void affichePokimac(Pokimac *pok);

int main() {

    int longueur = 0;
    int hauteur = 0;
    int nombrePokimac = 0 ;

    Joueur *joueur=new Joueur;

    // On affiche le menu
    menuDebut(&longueur, &hauteur, &nombrePokimac);
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

    Pokimac *pokimacTerrain = initPokimacTerrain(nombrePokimac, hauteur, longueur); //Liste des pokimac du terrain

    cout << "force : " << pokimacTerrain[0].force ;

    ConsoleUtils::clear();


    affichageTerrain(hauteur, longueur, tab, pokimacTerrain, &playerPos, nombrePokimac);

    while (joueur->nbPokimac != nombrePokimac){ //Tant que le joueur n'a pas 15 pokimacs --> on a pas gagné le jeu
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
                combat(joueur, &pokimacTerrain[i], hauteur, longueur, tab, pokimacTerrain, nombrePokimac);
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
    pokimacTerrain =new Pokimac[nombre];
    for (int i=0 ; i<nombre ; i++){
        pokimacTerrain[i].nom = "McLuhan";
        pokimacTerrain[i].espece = "électrique";
        pokimacTerrain[i].ascii = i+1  ;
        Attaque attaque1 ;
        Attaque attaque2 ;
       // pokimacTerrain[i].attaque1 = attaque1 ;
       // pokimacTerrain[i].attaque2 = attaque2 ;
        pokimacTerrain[i].defense = rand() % 100 + 1 ;
        pokimacTerrain[i].endurance = rand() % 100 + 1 ;
        pokimacTerrain[i].force = rand() % 100 + 1 ;
        pokimacTerrain[i].pv = 100 ;
        pokimacTerrain[i].position = {(rand() * ((hauteur-1) - 1) / RAND_MAX + 1 ), (rand() * ((longueur-1) - 1) / RAND_MAX + 1 )};
    }
    return pokimacTerrain ;
}

int combat(Joueur *joueur, Pokimac *pokRencontre, int hauteur, int longueur, char* tab, Pokimac* pokimacTerrain, int nombrePokimac){
    ConsoleUtils::clear();
    std::cout << "Combat" << std::endl;
    int choix ;
    //affichePokimac(pokRencontre) ;
    //affichePokimac(&(joueur->equipe[0]));
    cout << "1-Attaquer 2-Capturer 3-Donner une baie 4-Fuir 5-Inventaire:" << endl ;
    cin >> choix ;
    switch (choix) {
        case 1 :
            //Attaque
        break ;
        case 2 :
            if (joueur->inventaire.nbPokiball > 0){ //Le pokimac est capturé
               cout << "Vous lancez une pokiball sur " << pokRencontre->nom << endl ;
               joueur->inventaire.nbPokiball -- ;
               int reussite = rand() % 100 + 0 ;
               if (reussite>50){
                cout << "Bravo ! "<< pokRencontre->nom << " fait parti de votre équipe" << endl ;
                joueur->nbPokimac ++ ;
                joueur->equipe[joueur->nbPokimac] = *pokRencontre ;
                pokRencontre->position.x = -1000 ;
                pokRencontre->position.y = -1000 ;
                cout << joueur-> equipe[joueur->nbPokimac].position.x ; // C'est là qu'est le problème...
                sleep(3) ;
                ConsoleUtils::clear();
                affichageTerrain(hauteur, longueur, tab, pokimacTerrain, &(joueur->position), nombrePokimac);
                return 0 ;
               }else { // Le pokimac ne rentre pas
                cout << "Dommage..." << pokRencontre->nom << " est trop fort pour vous..." << endl ;
                sleep(3) ;
                combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac);
               }
            }else { // Il n'y a pas de pokiball dans l'inventaire
                sleep(3) ;
                cout << "Vous n'avez pas assez de pokiball !" ;
                ConsoleUtils::clear();
                affichageTerrain(hauteur, longueur, tab, pokimacTerrain, &(joueur->position), nombrePokimac);
                return 0 ;
            }
        break ;
        case 3 :
            //Baie
        break ;
        case 4 :
            cout << "Vous avez décidé de fuir" << endl ;
            sleep(3) ;
            ConsoleUtils::clear();
            affichageTerrain(hauteur, longueur, tab, pokimacTerrain, &(joueur->position), nombrePokimac);
            return 0 ;
        break ;
        case 5 :
            //Inventaire
        break ;
        default: break;
    }
    return 0 ;
}


void affichePokimac(Pokimac *pok){
    print_pokemon(pok->ascii) ;
    cout << pok->nom << endl ;
    cout << pok->espece << endl << endl ;
    cout << "Force : " << pok->force << endl ;
    cout << "Endurence : " << pok->endurance << endl ;
    cout << "Défense : " << pok->defense << endl ;
}


