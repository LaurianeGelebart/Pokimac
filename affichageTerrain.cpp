#include "consoleUtils.hpp"
#include "declarations.h"
#include "affichageTerrain.h"

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>
#include <iostream>


void affichageTerrain(int const hauteur, int const longueur, char* tab, Pokimac* pokimacTerrain, Position *playerPos, int nombrePokimac){

	//Remplir le tableau avec un pattern specifique
	for (int j=0; j<hauteur; j++) {
			for (int i=0; i<longueur; i++) {
				tab[j*longueur+i] = (i%(longueur-1) == 0 || j%(hauteur-1) == 0) ?  '#' : '.';
			}
		}

		// afficher le tableau à l'origine (0,0)
		ConsoleUtils::setCursorPos(0, 0);
		for (int j=0; j<hauteur; j++) {
			for (int i=0; i<longueur; i++) {
				std::cout << tab[j*longueur+i];
			}
			std::cout << std::endl;
		}

		ConsoleUtils::setCursorPos(playerPos->x, playerPos->y);
		std::cout << '@'; // Output '@' at my position
		for (int i=0 ; i<nombrePokimac ; i++){
            ConsoleUtils::setCursorPos(pokimacTerrain[i].position.x, pokimacTerrain[i].position.y);
            std::cout << 'P'; // Output 'P' at position of Pokimac
		}
}
