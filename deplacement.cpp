#include "consoleUtils.hpp"

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>
#include <iostream>
#include "declarations.h"
#include "deplacement.h"
#include "afficheASCII.h"

void combat(Joueur *joueur, Pokimac *pokRencontre);
void affichePokimac(Pokimac *pok);

void deplacement(Joueur *joueur, Pokimac *pok, int const hauteur, int const longueur,char* tab){

    Position oldPos; //ancienne position du joueur

    bool spaceHit = false;
	while (!spaceHit) {
		oldPos = joueur->position;
		bool special = false;
        int c = ConsoleUtils::getChar(&special); // attend le caractere special
        if(special) {
            switch (c) {
                case ConsoleUtils::KEY_UP:
                    if(joueur->position.y > 1) (joueur->position.y)--;
                    break;
                case ConsoleUtils::KEY_DOWN:
                    if(joueur->position.y < hauteur-2) (joueur->position.y)++; //-2 eviter de sortir du tableau
                    break;
                case ConsoleUtils::KEY_LEFT:
                    if(joueur->position.x > 1) (joueur->position.x)--; //-2 eviter de sortir du tableau
                    break;
                case ConsoleUtils::KEY_RIGHT:
                    if(joueur->position.x < longueur-2) (joueur->position.x)++;
                    break;
                default: break;
            }
        }
        else if (c == ' '){
			spaceHit = true;
        }

		if (joueur->position.x != oldPos.x || joueur->position.y != oldPos.y) {
			ConsoleUtils::setCursorPos(oldPos.x, oldPos.y);
			std::cout << tab[oldPos.y*longueur+oldPos.x]; // Clean
			ConsoleUtils::setCursorPos(joueur->position.x, joueur->position.y);
			std::cout << "@";
		}
		if ((joueur->position.x == pok->position.x) && (joueur->position.y == pok->position.y) ){
            combat(joueur, &joueur->equipe[0]);
		}
	}
}

void combat(Joueur *joueur, Pokimac *pokRencontre){
    ConsoleUtils::clear();
    std::cout << "Combat" << std::endl;
    affichePokimac(pokRencontre) ;
    affichePokimac(&(joueur->equipe[0]));
}

void affichePokimac(Pokimac *pok){
    print_pokemon(pok->ascii) ;
    cout << pok->nom << endl ;
    cout << pok->espece << endl << endl ;
    cout << "Force : " << pok->force << endl ;
    cout << "Endurence : " << pok->endurance << endl ;
    cout << "Défense : " << pok->defense << endl ;
}
