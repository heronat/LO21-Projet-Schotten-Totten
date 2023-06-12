//
// Created by Grzadziel Bartlomiej on 24/04/2023.
//

#include "Combinaison.h"
#include "Controleur.h"
/*
int Combinaison::calculerForceCombi()// MARCHE PAS !!!!! Ne fonctioone qu'en version classique, j'attends que les fonctions pour les modes de combat soient l�
{
    int pmin, pmil, pmax;
    pmin = min({ static_cast<int>(m_cartes[0]->getPuissance()),static_cast<int>(m_cartes[1]->getPuissance()), static_cast<int>(m_cartes[2]->getPuissance()) });
    pmax = max({ static_cast<int>(m_cartes[0]->getPuissance()),static_cast<int>(m_cartes[1]->getPuissance()), static_cast<int>(m_cartes[2]->getPuissance()) });
    pmil = static_cast<int>(m_cartes[0]->getPuissance()) + static_cast<int>(m_cartes[1]->getPuissance()) + static_cast<int>(m_cartes[2]->getPuissance()) - pmin - pmax;
    Couleur c1(m_cartes[0]->getCouleur()), c2(m_cartes[1]->getCouleur()), c3(m_cartes[2]->getCouleur());
    if (c1 == c2 && c2 == c3 && pmin +1 == pmil && pmil + 1 == pmax)
        return 4;
    if (pmin == pmil && pmil == pmax)
        return 3;
    if (c1 == c2 && c2 == c3)
        return 2;
    if (pmin +1 == pmil && pmil + 1 == pmax)
        return 1;
    return 0;
}
    */
int Combinaison::calculerForceCombi()
{
    auto nbr_carte = m_cartes.size();
    Couleur tab_coul[4];
    int tab_puis[4];
    for (auto i = 0; i < nbr_carte; i++) {
        tab_coul[i] = m_cartes[i]->getCouleur();
        tab_puis[i] = static_cast<int>(m_cartes[i]->getPuissance());
    }
    // on trie les puissance:
    for (auto i = 0; i < nbr_carte; i++) {
        for (auto j = 0; j < nbr_carte; j++) {
            if (tab_puis[i] < tab_puis[j]) {
                auto temp = tab_puis[i];
                tab_puis[i] = tab_puis[j];
                tab_puis[j] = temp;
            }
        }
    }
    // aff des tableaux:
    /*if (aff) {
        cout << endl;
        cout << "tableau des puissances: ";
        for (auto i = 0; i < nbr_carte; i++) {
            cout << tab_puis[i] << " ";
        }
        cout << endl;
        cout << "tableau des couleurs: ";
        for (auto i = 0; i < nbr_carte; i++) {
            cout << tab_coul[i] << " ";
        }
        cout << endl;
    }*/
    // 0 : somme, 1: suite, 2: couleur, 3: brelan, 4: suite couleur

    if (nbr_carte == 3) {
        if (tab_coul[0] == tab_coul[1] && tab_coul[1] == tab_coul[2] && tab_puis[0] + 1 == tab_puis[1] && tab_puis[1] + 1 == tab_puis[2]) {
            m_force_combi = 4;
            return 4;
        }
        if (tab_puis[0] == tab_puis[1] && tab_puis[1] == tab_puis[2]) {
            m_force_combi = 3;
            return 3;
        }
        if (tab_coul[0] == tab_coul[1] && tab_coul[1] == tab_coul[2]) {
            m_force_combi = 2;
            return 2;
        }
        if (tab_puis[0] + 1 == tab_puis[1] && tab_puis[1] + 1 == tab_puis[2]) {
            m_force_combi = 1;
            return 1;
        }

    }
    else if (nbr_carte == 4) {
        if (tab_coul[0] == tab_coul[1] && tab_coul[1] == tab_coul[2] && tab_coul[2] == tab_coul[3] && tab_puis[0] + 1 == tab_puis[1] && tab_puis[1] + 1 == tab_puis[2] && tab_puis[2] + 1 == tab_puis[3]){
            m_force_combi = 4;
            return 4;
        }
        if (tab_puis[0] == tab_puis[1] && tab_puis[1] == tab_puis[2] && tab_puis[2] == tab_puis[3]){
            m_force_combi = 3;
            return 3;
        }
        if (tab_coul[0] == tab_coul[1] && tab_coul[1] == tab_coul[2] && tab_coul[2] == tab_coul[3]){
            m_force_combi = 2;
            return 2;
        }
        if (tab_puis[0] + 1 == tab_puis[1] && tab_puis[1] + 1 == tab_puis[2] && tab_puis[2] + 1 == tab_puis[3]){
            m_force_combi = 1;
            return 1;
        }


    }
    m_force_combi = 0;
    return 0;
}

