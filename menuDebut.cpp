#include "consoleUtils.hpp"
#include "menuDebut.h"

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <unistd.h>

void menuDebut(int* longueur, int* hauteur, int* nombre, string* nom) {
    bool valid = false ;
    cout << "---------------------------Taille du terrain------------------------" << endl ;
    while(!valid){
        cout << "Hauteur (entre 20 et 50): " ;
        cin >> *hauteur ;
        if (*hauteur>=20 && *hauteur<=50){
            valid = true ;
        }else {
            cout << "Entrez un nombre entre 20 et 50." <<endl ;
        }
    }
    valid = false ;
    while(!valid){
        cout << "Longueur (entre 20 et 100): " ;
        cin >> *longueur ;
        if (*longueur>=20 && *longueur<=100){
            valid = true ;
        }else {
            cout << "Entrez un nombre entre 20 et 100." <<endl ;
        }
    }
    cout << "---------------------------Vous------------------------" << endl << "Quel est votre nom ? " ;
    cin >> *nom ;
    valid = false ;
    while(!valid){
        cout << "Combien de Pokimac voulez-vous attraper pour gagner le partie (10 max) ?" ;
        cin >> *nombre ;
        if (*nombre>0 && *nombre<11){
            valid = true ;
        }else {
            cout << "Entrez un nombre entre 1 et 10." <<endl ;
        }
    }
    ConsoleUtils::clear();
    cout << "Bienvenue dans le monde des Pokimacs " << *nom << " ! " << endl << "Dans ce monde merveilleux, pleins de pokimacs vivent heureux entre l'art et la Science. " << endl << "Pour en apprendre plus sur eux il te faut les rencontrer et les ajouter a ton equipe." << endl << "Tu as de la chance pour debuter ce jeu nous te confions un Marshall McMystherbe ! " << endl << "Tu dois y faire attention, si jamais tous les pokimacs de ton equipe sont K.O., l'aventure s'arrete pour toi.." << endl ;
    cout << "Appuie sur une touche pour continuer !" << endl;
    getch();
}
