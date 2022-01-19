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

void attaque(Joueur *joueur,Pokimac *pokRencontre,int hauteur,int longueur,char* tab,Pokimac* pokimacTerrain,int nombrePokimac, Position centerPos, int oldPokimac);
void seduire(Joueur *joueur,Pokimac *pokRencontre,int hauteur,int longueur,char* tab,Pokimac* pokimacTerrain,int nombrePokimac, Position centerPos, int oldPokimac);
void affichePokimac(Pokimac *pok);

using namespace std;

bool combat(Joueur *joueur, Pokimac *pokRencontre, int hauteur, int longueur, char* tab, Pokimac* pokimacTerrain, int nombrePokimac, Position centerPos, int oldPokimac){
    ConsoleUtils::clear();
    bool SomeoneAlive=false;
    bool validReponse = false ;

    for (int i=0;i<(joueur->nbPokimac);i++){
        if(joueur->equipe[i].pv > 0){
                SomeoneAlive=true;
        }
    }
    if(SomeoneAlive){
        cout << "Un " << pokRencontre->nom << " apparait !" << endl << endl;
        int choix ;
        affichePokimac(pokRencontre);
        affichePokimac(&(joueur->equipe[oldPokimac]));
        cout << "-----------------------------------------------------------------------------------" << endl << "Que voulez-vous faire ?" <<endl;
        cout << "1-Attaquer 2-Capturer 3-Donner une baie 4-Tentative de seduction 5-Fuir 6-Inventaire:" << endl ;
        while(!validReponse){
            cin >> choix ;
            if (choix>0 && choix<7){
                validReponse = true ;
            }else {
                cout << "Entrez un nombre entre 1 et 6." <<endl ;
            }
        }
        switch (choix) {
                    case 1 :
                        {//Attaque
                        attaque(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos, oldPokimac);
                        return false ;
                        }
                    break ;
                    case 2 : // Lancer une pokiball
                        {
                        if (joueur->inventaire.nbPokiball > 0){ //Le pokimac est capturé
                           cout << "Vous lancez une pokiball sur " << pokRencontre->nom << endl ;
                           joueur->inventaire.nbPokiball -- ;
                            if (pokRencontre->confiance>50 || pokRencontre->pv<(rand() % 30 + 1)){
                                cout << "Bravo ! "<< pokRencontre->nom << " fait parti de votre equipe" << endl ;
                                joueur->nbPokimac ++ ;
                                joueur->equipe[(joueur->nbPokimac)-1] = *pokRencontre ; // A
                                pokRencontre->position.x = longueur+2; // Pour faire disparaitre le pokiamc
                                pokRencontre->position.y = hauteur+2;
                                sleep(3) ;
                                ConsoleUtils::clear();
                                affichageTerrain(hauteur, longueur, tab, pokimacTerrain, &(joueur->position), nombrePokimac, centerPos);
                                return false ;
                            }else { // Le pokimac ne rentre pas
                                cout << "Dommage..." << pokRencontre->nom << " est trop fort pour vous..." << endl ;
                                sleep(3) ;
                                combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos, oldPokimac);
                            }
                        }else { // Il n'y a pas de pokiball dans l'inventaire
                            sleep(3) ;
                            cout << "Vous n'avez pas assez de pokiball !" ;
                            ConsoleUtils::clear();
                            affichageTerrain(hauteur, longueur, tab, pokimacTerrain, &(joueur->position), nombrePokimac, centerPos);
                        }
                        return false ;
                        }
                    break ;
                    case 3 : //Donner une baie
                        {
                        if (joueur->inventaire.nbBaie>0){
                            cout << "Vous donnez une baie a " << pokRencontre->nom << endl ;
                            joueur->inventaire.nbBaie -- ;
                            pokRencontre->confiance = pokRencontre->confiance + 6 ;
                            sleep(3) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos, oldPokimac);
                        } else {
                            cout << "Vous n'avez plus de baies... " << endl;
                            sleep(3) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos, oldPokimac);
                            }
                            return false;
                        }
                         break ;
                    case 4 : //Séduire
                        {
                        seduire(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos, oldPokimac);
                        return false ;
                        }
                    break ;
                    case 5 : //Fuir
                        {
                        cout << "Vous avez decide de fuir" << endl ;
                        sleep(3) ;
                        ConsoleUtils::clear();
                        affichageTerrain(hauteur, longueur, tab, pokimacTerrain, &(joueur->position), nombrePokimac, centerPos);
                        return false;
                        }
                    break ;
                    case 6 :
                        {
                        cout << "Voici le contenu de votre inventaire :" <<endl ;
                        cout << "Baies : " << joueur->inventaire.nbBaie << endl << "Pokiballs : " << joueur->inventaire.nbPokiball << endl ;
                        sleep(5) ;
                        ConsoleUtils::clear();
                        combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos, oldPokimac);
                        return false;
                        }
                    break ;
                    default: break;
                    }
    }
    else{
        cout << "Tous vos Pokimacs sont K.O. :'(" << endl;
        cout << "Appuie sur une touche pour continuer" << endl;
        }
return true;
}


void affichePokimac(Pokimac *pok){
    print_pokemon(pok->ascii) ;
    cout << endl;
    cout << "Nom : " << pok->nom << endl ;
    cout << "Espece : " <<pok->espece << endl << endl ;
    cout << "PV : " << pok->pv << endl;
    cout << "Force : " << pok->force << endl ;
    cout << "Endurance : " << pok->endurance << endl ;
    cout << "Defense : " << pok->defense << endl << endl ;
}

void seduire(Joueur *joueur,Pokimac *pokRencontre,int hauteur,int longueur,char* tab,Pokimac* pokimacTerrain,int nombrePokimac, Position centerPos, int oldPokimac){
    int choixSeduction ;
    bool validReponse = false ;
    cout << "Vous voulez tenter de plaire a " << pokRencontre->nom << endl << "Pour cela vous pouvez : " << endl << "1-Danse de seduction" << endl << "2-Faire une blague" << endl << "3-Declamer un poeme" << endl << "4-Retour" << endl;
    while(!validReponse){
        cin >> choixSeduction;
        if (choixSeduction>0 && choixSeduction<5){
            validReponse = true ;
        }else {
            cout << "Entrez un nombre entre 1 et 4." <<endl ;
        }
    }
    switch (choixSeduction){
                 case 1 : //Danse
                     {
                        int talentDanse = rand() % 100 + 1 ;
                        if (talentDanse>60){
                            cout << "Quel swing ! " << pokRencontre->nom << " vous aime de plus en plus !" << endl ;
                            pokRencontre->confiance = pokRencontre->confiance + 10 ;
                            sleep(5) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos, oldPokimac);
                        }else if (talentDanse>30 && talentDanse<=60){
                            cout << "Bon vous n'etes pas le danseur de l'annee mais au moins vous l'avez fait rire.. " << pokRencontre->nom << " vous trouve un peu plus sympathique !" << endl ;
                            pokRencontre->confiance = pokRencontre->confiance + 5 ;
                            sleep(8) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos, oldPokimac);
                        }else {
                            cout << "Dommage vous n'etes vraiment pas un bon danseur, tout ce que vous avez reussi a faire c'est lui faire peur..." << endl ;
                            pokRencontre->confiance = pokRencontre->confiance - 5 ;
                            sleep(8) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos, oldPokimac);
                        }
                     }
                break ;
                case 2 : //Blague
                    {
                        int talentBlague = rand() % 100 + 1 ;
                        if (talentBlague>60){
                            cout << pokRencontre->nom << " se roule par terre, bravo vous etes quelqu'un de drole !" << endl ;
                            pokRencontre->confiance = pokRencontre->confiance + 10 ;
                            sleep(5) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos, oldPokimac);
                        }else if (talentBlague>30 && talentBlague<=60){
                            cout << "Que fait une fraise sur un cheval ? Tagada Tagada" << endl << "Vous avez de la chance "<< pokRencontre->nom << " est aussi bete que vous, il a trouve ca drole..." << endl ;
                            pokRencontre->confiance = pokRencontre->confiance + 5 ;
                            sleep(8) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos, oldPokimac);
                        }else {
                            cout << "Peut-etre qu'insulter sa famille n'etait pas si drole que ca en fait... " << endl ;
                            pokRencontre->confiance = pokRencontre->confiance - 5 ;
                            sleep(5) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos, oldPokimac);
                        }
                    }
                break ;
                case 3 : //Poème
                    {
                        int talentPoeme = rand() % 100 + 1 ;
                        if (talentPoeme>60){
                            cout << "Rimbaud, Prevert, Verlaine, Hugo, ils n'ont aucun secret pour vous " << pokRencontre->nom << " adore !" << endl ;
                            pokRencontre->confiance = pokRencontre->confiance + 10 ;
                            sleep(5) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos, oldPokimac);
                        }else if (talentPoeme>30 && talentPoeme<=60){
                            cout << "Chanter du PNL est une idee originale" << endl << "Vous avez de la chance "<< pokRencontre->nom << " a eu l'air de trouver ca plus ou moins jolie." << endl ;
                            pokRencontre->confiance = pokRencontre->confiance + 5 ;
                            sleep(8) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos, oldPokimac);
                        }else {
                            cout << "Et non ! Votre cours d'arithmetique (bien que tres poetique pour vous), n'est pas un poeme. " << endl << "Vous faite un peu peur a " << pokRencontre->nom << " maintenant..." << endl ;
                            pokRencontre->confiance = pokRencontre->confiance - 5 ;
                            sleep(8) ;
                            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos, oldPokimac);
                        }
                    }
                break ;
                case 4 :
                    cout << "Vous vous degonflez, vous ne croyez pas assez en vous, c'est vraiment dommage." << endl << "Nous sommes pourtant certain que vous etiez un bon danseur... " << endl ;
                    pokRencontre->confiance = pokRencontre->confiance - 5 ;
                    sleep(7) ;
                    combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos, oldPokimac);
                break ;

            }
            sleep(3) ;
            ConsoleUtils::clear();
            affichageTerrain(hauteur, longueur, tab, pokimacTerrain, &(joueur->position), nombrePokimac, centerPos);
}


void attaque(Joueur *joueur,Pokimac *pokRencontre,int hauteur,int longueur,char* tab,Pokimac* pokimacTerrain,int nombrePokimac, Position centerPos, int oldPokimac){
    bool Alive = false;
    bool validReponse = false ;
    int choixPokimac;
    do{
        cout << "Quel pokimac voulez-vous deployer ?" << endl;
        for (int i=0;i<(joueur->nbPokimac);i++){
                cout << i+1 << "-" << joueur->equipe[i].nom << endl;
        }
        while(!validReponse){
                cin >> choixPokimac;
                if (choixPokimac>0 && choixPokimac<=joueur->nbPokimac){
                        validReponse = true ;
                }else {
                        cout << "Entrez un nombre entre 1 et " << joueur->nbPokimac <<endl ;
                }
        }
        choixPokimac -= 1;
        validReponse=false;
        oldPokimac =choixPokimac;
        if((joueur->equipe[choixPokimac].pv) <= 0){
            cout << joueur->equipe[choixPokimac].nom << " est K.O., choisis en un autre !" << endl;
        }
        else{
            Alive=true;
        }
        }while (!Alive);
            //Dégats du joueur
            joueur->equipe[choixPokimac].attaque1.puissance = (joueur->equipe[choixPokimac].force)-(0.3*(pokRencontre->defense));
            joueur->equipe[choixPokimac].attaque2.puissance = (joueur->equipe[choixPokimac].endurance)-(0.25*(pokRencontre->defense));

            //Dégats du Pokimac rencontré
            pokRencontre->attaque1.puissance = (pokRencontre->force)-(0.3*(joueur->equipe[choixPokimac].defense));
            pokRencontre->attaque2.puissance = (pokRencontre->endurance)-(0.25*(joueur->equipe[choixPokimac].defense));

            //Cas ou les attaques prennent des valeurs négatives
            if((joueur->equipe[choixPokimac].attaque1.puissance)<0){
                joueur->equipe[choixPokimac].attaque1.puissance = 0;
            }
            if((pokRencontre->attaque1.puissance)<0){
                pokRencontre->attaque1.puissance = 0;
            }
            if((joueur->equipe[choixPokimac].attaque2.puissance)<0){
                joueur->equipe[choixPokimac].attaque2.puissance = 0;
            }
            if((pokRencontre->attaque2.puissance)<0){
                pokRencontre->attaque2.puissance = 0;
            }

            cout << joueur->equipe[choixPokimac].nom << " en avant !" << endl;
            sleep(2);
            ConsoleUtils::clear();
            cout << "Que dois-faire " << joueur->equipe[choixPokimac].nom << " ?" << endl;
            cout << "1- " << joueur->equipe[choixPokimac].attaque1.nom <<endl;
            cout << "2- " << joueur->equipe[choixPokimac].attaque2.nom <<endl;
            int choixAttaque;
            validReponse = false ;
            while(!validReponse){
                cin >> choixAttaque;
                if (choixAttaque>0 && choixAttaque<3){
                    validReponse = true ;
                }else {
                    cout << "Entrez un nombre entre 1 et 2." <<endl ;
                }
            }

            if (choixAttaque==1){
                cout << "Votre " << joueur->equipe[choixPokimac].nom << " utilise " << joueur->equipe[choixPokimac].attaque1.nom << endl;
                pokRencontre->pv = (pokRencontre->pv) - (joueur->equipe[choixPokimac].attaque1.puissance);
            }else{
                cout <<"Votre "<<joueur->equipe[choixPokimac].nom << " utilise " << joueur->equipe[choixPokimac].attaque2.nom << endl;
                pokRencontre->pv = (pokRencontre->pv) - (joueur->equipe[choixPokimac].attaque2.puissance);
            }
            sleep(3);
            ConsoleUtils::clear();

            affichePokimac(pokRencontre);
            sleep(3);
            if(pokRencontre->pv>0){
                int choixAttaquePokrencontre = rand() % 2 + 1; // choisi attaque1 ou attaque2
                if (choixAttaquePokrencontre==1){
                    cout <<"Le " << pokRencontre->nom << " sauvage utilise " << pokRencontre->attaque1.nom << endl;
                    joueur->equipe[choixPokimac].pv = (joueur->equipe[choixPokimac].pv) - (pokRencontre->attaque1.puissance);
                }else{
                    cout <<"Le " << pokRencontre->nom << " sauvage utilise " << pokRencontre->attaque2.nom << endl;
                    joueur->equipe[choixPokimac].pv = (joueur->equipe[choixPokimac].pv) - (pokRencontre->attaque2.puissance);
                }
            }else {
                cout << "Vous avez battu " << pokRencontre->nom << " mais pas d'inquietude dans ce monde les pokimacs ne meurent pas. " << endl << "Tu peux toujours l'ajouter a ton equipe, mais n'oublie pas d'aller le soigner au centre pokimac !" << endl ;
                sleep(10);
            }

            sleep(3);
            ConsoleUtils::clear();
            combat(joueur, pokRencontre, hauteur, longueur, tab, pokimacTerrain, nombrePokimac, centerPos, oldPokimac);
}



