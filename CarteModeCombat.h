//
// Created by Utilisateur on 19/04/2023.
//

#ifndef LO21_SCHOTTEN_TOTTEN_CARTEMODECOMBAT_H
#define LO21_SCHOTTEN_TOTTEN_CARTEMODECOMBAT_H
#include "CarteTactique.h"
#include "Borne.h"

class CarteModeCombat : public CarteTactique {
public:
    CarteModeCombat(const string& nom) : CarteTactique(nom)  {};

    static void jouer_ColinMaillard(Borne* b)  {
        b->setCollin(true);
	}
    static void jouer_CombatdeBoue(Borne *b)  {
        b->setBoue(true);
    }

    void afficherCarte()const override{
        if(getNom()=="Colin Maillard"){
            cout<< "| Col Mail |";
        }
        else if(getNom()=="Combat de Boue"){
            cout<< "| Cbt Boue |";
        }
    }

    void afficherDosCarte()const override {
        cout << "| Tactique |";
    }
		
};
#endif //LO21_SCHOTTEN_TOTTEN_CARTEMODECOMBAT_H
