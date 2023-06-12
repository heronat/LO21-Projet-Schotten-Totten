//
// Created by Utilisateur on 26/04/2023.
//

#ifndef LO21_SCHOTTEN_TOTTEN_MAIN_JOUEUR_H
#define LO21_SCHOTTEN_TOTTEN_MAIN_JOUEUR_H
#include "Carte.h"
#include<iostream>
#include<string>
#include <vector>


class Main {
    int m_taille;
    vector<Carte*> m_cartes;
    bool m_joker;
    int m_nbr_carte_tactique_joue;
public:
    friend class Joueur;

    explicit Main(int taille) : m_taille(0), m_cartes(0), m_joker(false), m_nbr_carte_tactique_joue(0) {

    };

    int getTaille() const {
        // Ou retrun m_cartes.size() ?
        return m_taille;
    }
    void supprimerCarte(int indice) {
        m_cartes.erase(m_cartes.begin() + indice);
        m_taille = m_cartes.size();
    }

    vector<Carte*> getCartes() { // const ou pas ?
        return m_cartes;
    }

    Carte* getCarte(int i) const {
        return m_cartes[i];
    }

    bool getJoker() const {
        return m_joker;
    }

    int getNbrCarteTactiqueJoue() const {
        return m_nbr_carte_tactique_joue;
    }

    void ajouterCarte(Carte* carte) {
        m_cartes.push_back(carte);
    }


};

#endif //LO21_SCHOTTEN_TOTTEN_MAIN_JOUEUR_H