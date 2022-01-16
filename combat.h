#ifndef COMBAT_H
#define COMBAT_H

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

int combat(Joueur *joueur, Pokimac *pokRencontre, int hauteur, int longueur, char* tab, Pokimac* pokimacTerrain, int nombrePokimac, Position centerPos) ;
void affichePokimac(Pokimac *pok);


#endif // COMBAT_H
