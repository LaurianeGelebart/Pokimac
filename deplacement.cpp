#include "consoleUtils.hpp"

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>
#include <iostream>
#include "declarations.h"
#include "deplacement.h"


void deplacement(Joueur *joueur, int const hauteur, int const longueur,char* tab, int c){

    Position oldPos; //ancienne position du joueur

   /* bool spaceHit = false;
	while (!spaceHit) { */
		//oldPos = joueur->position;
	//	bool special = false;
    //    int c = ConsoleUtils::getChar(&special); // attend le caractere special
   //     if(special) {
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
     //   }
     //   else if (c == ' '){
	//		spaceHit = true;
    //    }


	//}
}



