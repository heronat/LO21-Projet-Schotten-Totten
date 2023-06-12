//
// Created by Utilisateur on 23/04/2023.
//

#ifndef LO21_SCHOTTEN_TOTTEN_PIOCHE_H
#define LO21_SCHOTTEN_TOTTEN_PIOCHE_H

#include "JeuClan.h"
#include "JeuTactique.h"
#include <cstddef>

class Pioche
{
    const Carte** m_cartes;
    size_t m_nb;

public:
    Pioche(const JeuClan& jeuClan);
    Pioche(const JeuTactique& jeuTactique);
    void push_back(const Carte* carte) {
        const Carte** temp = new const Carte*[m_nb + 1];
        for (size_t i = 0; i < m_nb; ++i) {
            temp[i] = m_cartes[i];
        }
        temp[m_nb] = carte;

        delete[] m_cartes;
        m_cartes = temp;
        ++m_nb;
    }
    void push_back2(const Carte* carte) {

        m_cartes[++m_nb] = carte;
    }
    bool estVide() const { return m_nb==0; }
    size_t getNbCartes() const { return m_nb; }
    const CarteClan& piocherCarteClan();
    const CarteTactique& piocherCarteTactique();
    const CarteTroupeElite& piocherCarteTroupeElite();
    int quandjepiochejefaisattention();
    const Carte& piocher();
    ~Pioche();

    Pioche(const Pioche&) = delete;
    Pioche& operator=(const Pioche&) = delete;
};


#endif //LO21_SCHOTTEN_TOTTEN_PIOCHE_H
