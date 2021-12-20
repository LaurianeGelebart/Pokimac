#include "consoleUtils.hpp"

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>
#include <iostream>
#include "declarations.h"
#include "deplacement.h"



void deplacement(Position *playerPos, Position *pokimacPos, Position *oldPos, int const hauteur, int const longueur){
    bool spaceHit = false;

	while (!spaceHit) {
		oldPos = playerPos;
		bool special = false;
        char c = ConsoleUtils::getChar(&special);// Get
		switch (c) {
			case 'z':
				if((*playerPos).y > 1) --(*playerPos).y;
				break;
			case 's':
				if((*playerPos).y < hauteur) ++(*playerPos).y;
				break;
			case 'q':
				if((*playerPos).x > 1) --(*playerPos).x;
				break;
			case 'd':
				if((*playerPos).x < longueur) ++(*playerPos).x;
				break;
			case ' ': spaceHit = true; break;
			default: break;
		}

		if ((*playerPos).x != (*oldPos).x || (*playerPos).y != (*oldPos).y) {
			ConsoleUtils::setCursorPos((*oldPos).x, (*oldPos).y); std::cout << ' '; // Clean
			ConsoleUtils::setCursorPos((*playerPos).x, (*playerPos).y); std::cout << "@";
		}
		if (((*playerPos).x == (*pokimacPos).x) && ((*playerPos).y == (*pokimacPos).y) ){
            ConsoleUtils::clear();
            std::cout << "Combat" << std::endl;
		}
	}
}
