#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include "consoleUtils.hpp"

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>

#include <iostream>

using namespace std;

// Definir Position
struct Position {
	int x;
	int y;
};


typedef struct Attaque{
    string nom ;
    int puissance ;
} Attaque ;

typedef struct Inventaire{
    int nbPokiball ;
    int nbBaie ;
} Inventaire ;

typedef struct Pokimac{
    string espece ;
    int ascii ;
    string nom ;
    Attaque attaque1 ;
    Attaque attaque2 ;
    int pv ;
    int endurance ;
    int force ;
    int defense ;
    Position position ;
    int confiance ; // = envie de rentrer dans la pokiball
} Pokimac ;

typedef struct Joueur{
    string nom ;
    Pokimac* equipe ;
    int nbPokimac ;
    Inventaire inventaire ;
    Position position ;
} Joueur ;

#endif // DECLARATIONS_H
