#include "consoleUtils.hpp"

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>
#include <iostream>
#include "declarations.h"
#include "deplacement.h"



void deplacement(Position *playerPos, Position *pokimacPos, int const hauteur, int const longueur,char* tab){

    Position oldPos; //ancienne position du joueur

    bool spaceHit = false;
	while (!spaceHit) {
		oldPos = *playerPos;
		bool special = false;
        int c = ConsoleUtils::getChar(&special); // attend le caractere special
        if(special) {
            switch (c) {
                case ConsoleUtils::KEY_UP:
                    if(playerPos->y > 1) (playerPos->y)--;
                    break;
                case ConsoleUtils::KEY_DOWN:
                    if(playerPos->y < hauteur-2) (playerPos->y)++; //-2 eviter de sortir du tableau
                    break;
                case ConsoleUtils::KEY_LEFT:
                    if(playerPos->x > 1) (playerPos->x)--; //-2 eviter de sortir du tableau
                    break;
                case ConsoleUtils::KEY_RIGHT:
                    if(playerPos->x < longueur-2) (playerPos->x)++;
                    break;
                default: break;
            }
        }
        else if (c == ' '){
			spaceHit = true;
        }

		if ((*playerPos).x != oldPos.x || (*playerPos).y != oldPos.y) {
			ConsoleUtils::setCursorPos(oldPos.x, oldPos.y);
			std::cout << tab[oldPos.y*longueur+oldPos.x]; // Clean
			ConsoleUtils::setCursorPos((*playerPos).x, (*playerPos).y);
			std::cout << "@";
		}
		if (((*playerPos).x == (*pokimacPos).x) && ((*playerPos).y == (*pokimacPos).y) ){
            ConsoleUtils::clear();
            std::cout << "Combat" << std::endl;
		}
	}
}
