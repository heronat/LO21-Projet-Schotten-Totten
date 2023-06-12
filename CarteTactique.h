//
// Created by Utilisateur on 19/04/2023.
//

#ifndef LO21_SCHOTTEN_TOTTEN_CARTETACTIQUE_H
#define LO21_SCHOTTEN_TOTTEN_CARTETACTIQUE_H
#include"Carte.h"


class CarteTactique : public Carte {
    const string m_nom;
public:
    CarteTactique(const string& nom): m_nom(nom) {};
    const string &getNom() const { return m_nom; }
    void afficherCarte()const override{
        cout<<"Carte Tactique vide";
    };
};

#endif //LO21_SCHOTTEN_TOTTEN_CARTETACTIQUE_H
