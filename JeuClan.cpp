//
// Created by Utilisateur on 23/04/2023.
//

#include "JeuClan.h"
#include "CarteClan.h"



    JeuClan::JeuClan()
    {
        size_t i = 0;
        for (auto c : Couleurs)
            for (auto p : Puissances)
                cartes[i++] = new CarteClan(p, c);
    }


    JeuClan::~JeuClan()
    {
        for (size_t i = 0; i < getNbCartes(); i++)
            delete cartes[i];
    }

    JeuClan & JeuClan::getJeuClan()
    {
        if (handler.jeu == nullptr)
            handler.jeu = new JeuClan;
        return *handler.jeu;
    }

    void JeuClan::libererJeuClan()
    {
        delete handler.jeu;
        handler.jeu =nullptr;
    }

    JeuClan::Handler JeuClan::handler = Handler();
