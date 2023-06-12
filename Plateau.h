//
// Created by Utilisateur on 26/04/2023.
//

#ifndef LO21_SCHOTTEN_TOTTEN_PLATEAU_H
#define LO21_SCHOTTEN_TOTTEN_PLATEAU_H

#include "Joueur.h"
#include "Carte.h"
#include "Borne.h"
#include "CarteTactique.h"

class Plateau {
    Joueur * m_joueur1; // Ou de type Joueur ?
    Joueur * m_joueur2;
    int m_joueur_actif;
    vector<Carte*> m_defausse;
    Borne **m_bornes ;
public:
    friend class Controleur;

    Plateau(int taille, bool ia1, bool ia2) : m_joueur1(nullptr), m_joueur2(nullptr), m_joueur_actif(1), m_bornes{new Borne*[9]} {
        m_joueur1 = new Joueur(taille, ia1);
        m_joueur2 = new Joueur(taille, ia2);
        for (int i = 0; i < 9; ++i) {
			m_bornes[i] = new Borne(i+1);
		}
    };

    Joueur* getJoueur1()   {  // const ou pas ?
        return m_joueur1;
    }

    Joueur* getJoueur2()  { // const ou pas ?
        return m_joueur2;
    }

    int getJoueurActif() const {
        return m_joueur_actif;
    }

    vector<Carte*> getDefausse() const {
        return m_defausse;
    }

    Borne* getBornes(int i) const{
        return m_bornes[i];
    }

    void setJoueurActif(int joueurActif) {
        m_joueur_actif = joueurActif;
    }

    void poser(Borne borne, CarteClan* carte);

    void afficherMainJoueur(int joueur);
    void afficherDosMain(int joueur);
    void afficherBornes(int joueur);
    void afficherPlateau(int pointdevue);

    Plateau(const Plateau&) = delete;
    Plateau& operator=(const Plateau&) = delete;
};

#endif //LO21_SCHOTTEN_TOTTEN_PLATEAU_H
