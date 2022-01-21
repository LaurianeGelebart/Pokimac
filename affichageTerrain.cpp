#include "consoleUtils.hpp"
#include "declarations.h"
#include "affichageTerrain.h"

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>
#include <iostream>


void affichageTerrain(int const hauteur, int const longueur, char* tab, Pokimac* pokimacTerrain, Position *playerPos, int nombrePokimac, Position centerPos){

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

		for (int i=0 ; i<nombrePokimac ; i++){
            ConsoleUtils::setCursorPos(pokimacTerrain[i].position.x, pokimacTerrain[i].position.y);
            ConsoleUtils::setColor(static_cast<ConsoleUtils::Color>(2)); //VERT
            std::cout << 'P'; // Output 'P' at position of Pokimac
		}

		ConsoleUtils::setCursorPos(centerPos.x, centerPos.y);
		ConsoleUtils::setColor(static_cast<ConsoleUtils::Color>(4)); //ROUGE
		std::cout << 'C'; // Output 'C' at the center pokimac position

        ConsoleUtils::setCursorPos((longueur+2),(hauteur+2));
        std::cout << ' '; // Output ' ' at position of Pokimac

        ConsoleUtils::setCursorPos(playerPos->x, playerPos->y);
        ConsoleUtils::setColor(static_cast<ConsoleUtils::Color>(3)); //BLEU
		std::cout << '@'; // Output '@' at my position

		ConsoleUtils::setColor(static_cast<ConsoleUtils::Color>(7)); //WHITE
}
