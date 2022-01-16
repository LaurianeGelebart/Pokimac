#include "consoleUtils.hpp"
#include "declarations.h"
#include "affichageTerrain.h"
#include "deplacement.h"
#include "menuDebut.h"
#include "afficheASCII.h"
#include "afficheASCII.h"


#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <string>
#include <typeinfo>
#include <Windows.h>
#include <unistd.h>

#include <iostream>


void seduire(Joueur *joueur,Pokimac *pokRencontre,int hauteur,int longueur,char* tab,Pokimac* pokimacTerrain,int nombrePokimac, Position centerPos);

using namespace std;

int combat(Joueur *joueur, Pokimac *pokRencontre, int hauteur, int longueur, char* tab, Pokimac* pokimacTerrain, int nombrePokimac, Position centerPos){
    ConsoleUtils::clear();
    std::cout << "Combat" << std::endl;
    int choix ;
    //affichePokimac(pokRencontre) ;
    //affichePokimac(&(joueur->equipe[0]));
    cout << "1-Attaquer 2-Capturer 3-Donner une baie 4-Tentative de seduction 5-Fuir 6-Inventaire:" << endl ;
    cin >> choix ;
    switch (choix) {
        case 1 :
            //Attaque
        break ;
        case 2 : // Lancer une pokiball
            if (joueur->inventaire.nbPokiball > 0){ //Le pokimac est capturé
               cout << "Vous lancez une pokiball sur " << pokRencontre->nom << endl ;
               joueur->inventaire.nbPokiball -- ;
               if (pokRencontre->confiance>50 || pokRencontre->pv<30){
                cout << "Bravo ! "<< pokRencontre->nom << " fait parti de votre équipe" << endl ;
                joueur->nbPokimac ++ ;
                joueur->equipe[joueur->nbPokimac] = *pokRencontre ; // A
                pokRencontre->position.x = -1000 ; // Pour faire disparaitre le pokiamc
                pokRencontre->position.y = -1000 ;
                cout << joueur-> equipe[joueur->nbPokimac].position.x ; // C'est là qu'est le problème...
                sleep(3) ;
                ConsoleUtils::clear();
                affichageTerrain(hauteur, longueur, tab, pokimacTerrain, &(joueur->position), nombrePokimac, centerPos);
                return 0 ;
               }else { // Le pokimac ne rentre pas
                cout << "Dommage..." << pokRencontre->nom << " est trop fort pour vous..." << endl ;
                sleep(3) ;
                combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos);
               }
            }else { // Il n'y a pas de pokiball dans l'inventaire
                sleep(3) ;
                cout << "Vous n'avez pas assez de pokiball !" ;
                ConsoleUtils::clear();
                affichageTerrain(hauteur, longueur, tab, pokimacTerrain, &(joueur->position), nombrePokimac, centerPos);
                return 0 ;
            }
        break ;
        case 3 : //Donner une baie
            if (joueur->inventaire.nbBaie>0){
                cout << "Vous donnez une baie à " << pokRencontre->nom << endl ;
                joueur->inventaire.nbBaie -- ;
                //pokRencontre->confiance = pokRencontre->confiance + 6 ;
                cout << pokRencontre->confiance << endl ;
                sleep(3) ;
                combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos);
            } else {
                cout << "Vous n'avez plus de baies... " << endl;
                sleep(3) ;
                combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos);
            }
        break ;
        case 4 : //Séduire
            seduire(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos);
            return 0 ;
        break ;
        case 5 : //Fuir
            cout << "Vous avez decide de fuir" << endl ;
            sleep(3) ;
            ConsoleUtils::clear();
            affichageTerrain(hauteur, longueur, tab, pokimacTerrain, &(joueur->position), nombrePokimac, centerPos);
            return 0 ;
        break ;
        case 6 :
            //Inventaire
        break ;
        default: break;
    }
    return 0 ;
}


void affichePokimac(Pokimac *pok){
    print_pokemon(pok->ascii) ;
    cout << pok->nom << endl ;
    cout << pok->espece << endl << endl ;
    cout << "Force : " << pok->force << endl ;
    cout << "Endurance : " << pok->endurance << endl ;
    cout << "Défense : " << pok->defense << endl ;
}

void seduire(Joueur *joueur,Pokimac *pokRencontre,int hauteur,int longueur,char* tab,Pokimac* pokimacTerrain,int nombrePokimac, Position centerPos){
    int choixSeduction ;
    cout << "Vous voulez tenter de plaire à " << pokRencontre->nom << endl << "Pour cela vous pouvez : " << endl << "1-Danse de seduction" << endl << "2-Faire une blague" << endl << "3-Declamer un poème" << endl << "4-Retour" << endl;
    cin >> choixSeduction ;
            switch (choixSeduction){
                 case 1 : //Danse
                     {
                        int talentDanse = rand() % 100 + 1 ;
                        if (talentDanse>60){
                            cout << "Quel swing ! " << pokRencontre->nom << " vous aime de plus en plus !" << endl ;
                            pokRencontre->confiance = pokRencontre->confiance + 10 ;
                            sleep(3) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos);
                        }else if (talentDanse>30 && talentDanse<=60){
                            cout << "Bon vous n'etes pas le danseur de l'annee mais au moins vous l'avez fait rire.. " << pokRencontre->nom << " vous trouve un peu plus sympathique !" << endl ;
                            pokRencontre->confiance = pokRencontre->confiance + 5 ;
                            sleep(3) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos);
                        }else {
                            cout << "Dommage vous n'etes vraiment pas un bon danseur, tout ce que vous avez reussi a faire c'est lui faire peur..." << endl ;
                            pokRencontre->confiance = pokRencontre->confiance - 5 ;
                            sleep(3) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos);
                        }
                     }
                break ;
                case 2 : //Blague
                    {
                        int talentBlague = rand() % 100 + 1 ;
                        if (talentBlague>60){
                            cout << pokRencontre->nom << " se roule par terre, bravo vous etes quelqu'un de drole !" << endl ;
                            pokRencontre->confiance = pokRencontre->confiance + 10 ;
                            sleep(3) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos);
                        }else if (talentBlague>30 && talentBlague<=60){
                            cout << "Que fait une fraise sur un cheval ? Tagada Tagada" << endl << "Vous avez de la chance "<< pokRencontre->nom << " est aussi bete que vous il a trouve ca drole..." << endl ;
                            pokRencontre->confiance = pokRencontre->confiance + 5 ;
                            sleep(3) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos);
                        }else {
                            cout << "Peut-etre qu'insulter sa famille n'etait pas si drole que ca en fait... " << endl ;
                            pokRencontre->confiance = pokRencontre->confiance - 5 ;
                            sleep(3) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos);
                        }
                    }
                break ;
                case 3 : //Poème
                    {
                        int talentPoeme = rand() % 100 + 1 ;
                        if (talentPoeme>60){
                            cout << "Rimbaud, Prevert, Verlaine, Hugo, ils n'ont aucun secret pour vous " << pokRencontre->nom << " adore !" << endl ;
                            pokRencontre->confiance = pokRencontre->confiance + 10 ;
                            sleep(3) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos);
                        }else if (talentPoeme>30 && talentPoeme<=60){
                            cout << "Chanter du PNL est une idee originale" << endl << "Vous avez de la chance "<< pokRencontre->nom << " a eu l'air de trouver ca plus ou moins jolie." << endl ;
                            pokRencontre->confiance = pokRencontre->confiance + 5 ;
                            sleep(3) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos);
                        }else {
                            cout << "Et non ! Votre cours d'arithmetique (bien que tres poetique pour vous), n'est pas un poeme, vous faite un peu peur a " << pokRencontre->nom << " maintenant..." << endl ;
                            pokRencontre->confiance = pokRencontre->confiance - 5 ;
                            sleep(3) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos);
                        }
                    }
                break ;
                case 4 :
                    cout << "Vous vous degonflez, vous ne croyez pas assez en vous, c'est vraiment dommage, nous sommes pourtant certain que vous etiez un bon danseur... " << endl ;
                    pokRencontre->confiance = pokRencontre->confiance - 5 ;
                    sleep(3) ;
                    combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos);
                break ;

            }
            sleep(3) ;
            ConsoleUtils::clear();
            affichageTerrain(hauteur, longueur, tab, pokimacTerrain, &(joueur->position), nombrePokimac, centerPos);
}


