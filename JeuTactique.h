//
// Created by Utilisateur on 23/04/2023.
//

#ifndef LO21_SCHOTTEN_TOTTEN_JEUTACTIQUE_H
#define LO21_SCHOTTEN_TOTTEN_JEUTACTIQUE_H

#pragma once
#include "Carte.h"
#include "CarteException.h"
#include "CarteRuse.h"
#include "CarteModeCombat.h"
#include "CarteTroupeElite.h"
#include <cstddef>

class JeuTactique {

    const Carte* cartes[10];

    JeuTactique();
    ~JeuTactique();
    JeuTactique(const JeuTactique& j) = delete;
    JeuTactique& operator=(const JeuTactique& j) = delete;

    struct Handler
    {
        JeuTactique* jeu;
        Handler() : jeu(nullptr) {}
        ~Handler() { delete jeu; }
    };

    static Handler handler;

    const Carte& getCarte(size_t i) const
    {
        if(i>=81) throw CarteException("La carte est invalide");
        return *cartes[i];
    }

public:
    friend class Controleur;

    static JeuTactique & getJeuTactique();
    static void libererJeuTactique();

    size_t getNbCartes() const { return 10; }


    class Iterator {
        friend class JeuTactique;
        size_t i;
        Iterator() : i(0) {};

    public:
        bool isDone() const { return i== JeuTactique::getJeuTactique().getNbCartes(); }
        void next()
        {
            if(isDone())
                throw CarteException("Iterateur a fini de parcourir la sequence");
            i++;
        }

        const Carte& currentItem() const {
            if (isDone()) throw CarteException("Iterateur a fini de parcourir la sequence");
            return JeuTactique::getJeuTactique().getCarte(i);
        }

    };
    Iterator getIterator() const
    {
        return Iterator();
    }


};



#endif //LO21_SCHOTTEN_TOTTEN_JEUTACTIQUE_H
