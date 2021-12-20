#include "consoleUtils.hpp"
#include "declarations.h"
#include "affichageTerrain.h"

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>
#include <iostream>


void affichageTerrain(int const hauteur, int const longueur, Position pokimacPos, Position *playerPos){

	int i;
	int j;

	// initial display
    ConsoleUtils::setCursorPos(0,0); std::cout << '+';
	for (i=1; i<=longueur; i++){
        int x=0;
        ConsoleUtils::setCursorPos(x,i); std::cout << '|';
	}
	for (i=1; i<=longueur; i++){
        int x=hauteur+1;
        ConsoleUtils::setCursorPos(x,i); std::cout << '|';
	}
	for (j=1; j<=hauteur; j=j+1){
        int y=0;
        ConsoleUtils::setCursorPos(j,y); std::cout << "-";
	}
	for (j=1; j<=hauteur; j=j+1){
        int y=longueur+1;
        ConsoleUtils::setCursorPos(j,y); std::cout << "-";
	}

	ConsoleUtils::setCursorPos(0,longueur+1); std::cout << '+';
	ConsoleUtils::setCursorPos(hauteur+1,0); std::cout << '+';
	ConsoleUtils::setCursorPos(hauteur+1,longueur+1); std::cout << '+';

    ConsoleUtils::setColor(static_cast<ConsoleUtils::Color>(2)); //vert

	ConsoleUtils::setCursorPos(pokimacPos.x, pokimacPos.y); std::cout << 'P';
	ConsoleUtils::setCursorPos(playerPos->x, playerPos->y); std::cout << "@";

}
