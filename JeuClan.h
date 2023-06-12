//
// Created by Utilisateur on 23/04/2023.
//

#ifndef LO21_SCHOTTEN_TOTTEN_JEUCLAN_H
#define LO21_SCHOTTEN_TOTTEN_JEUCLAN_H

#pragma once
#include "Carte.h"
#include "CarteException.h"
#include <cstddef>

class JeuClan {

    const Carte* cartes[54];
    JeuClan();
    ~JeuClan();
    JeuClan(const JeuClan& j) = delete;
    JeuClan& operator=(const JeuClan& j) = delete;

    struct Handler
    {
        JeuClan* jeu;
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

    static JeuClan & getJeuClan();
    static void libererJeuClan();

    size_t getNbCartes() const { return 54; }


    class Iterator {
        friend class JeuClan;
        size_t i;
        Iterator() : i(0) {};

    public:
        bool isDone() const { return i== JeuClan::getJeuClan().getNbCartes(); }
        void next()
        {
            if(isDone())
                throw CarteException("Iterateur a fini de parcourir la sequence");
            i++;
        }

        const Carte& currentItem() const {
            if (isDone()) throw CarteException("Iterateur a fini de parcourir la sequence");
            return JeuClan::getJeuClan().getCarte(i);
        }

    };
    Iterator getIterator() const
    {
        return Iterator();
    }



};

#endif //LO21_SCHOTTEN_TOTTEN_JEUCLAN_H
