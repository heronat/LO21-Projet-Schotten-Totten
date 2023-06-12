//
// Created by Utilisateur on 19/04/2023.
//

#ifndef LO21_SCHOTTEN_TOTTEN_CARTE_H
#define LO21_SCHOTTEN_TOTTEN_CARTE_H
#include<iostream>
#include<string>
#include"CarteException.h"
#include <vector>

using namespace std;

class Carte {

public:

    // Necessaire pour utiliser dynamic_cast
    virtual ~Carte() {};
    virtual void afficherCarte()const{
        cout<<"Carte vide";
    };
    virtual void afficherDosCarte()const{
        cout<<"Dos Carte vide";
    };
};

void affichage_vecteur_carte(vector<Carte*> v);
void affichage_vecteur_carte2(vector<struct CarteClan *> v); //temporaire juste pour l'affichage dans le main

#endif //LO21_SCHOTTEN_TOTTEN_CARTE_H
