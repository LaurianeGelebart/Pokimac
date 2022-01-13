#include "consoleUtils.hpp"
#include "menuDebut.h"

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>

#include <iostream>

void menuDebut(int* longueur, int* hauteur, int* nombre) {
    cout << "Longueur puis hauteur du terrain :" << endl ;
    cin >> *longueur >> *hauteur;
    cout << "Nombre pokimac à capturer :" << endl ;
    cin >> *nombre;
}
