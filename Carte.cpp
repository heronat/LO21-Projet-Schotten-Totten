//
// Created by Utilisateur on 19/04/2023.
//

#include "Carte.h"
#include "CarteClan.h"
#include "CarteTactique.h"
#include "CarteTroupeElite.h"
#include "vector"

void affichage_vecteur_carte(vector<Carte*> v) {
    auto i = 0;
    for (auto carte: v) {
        if (CarteTroupeElite * carte_troupe_elite = dynamic_cast<CarteTroupeElite *>(carte)) {
            cout << i <<"  CarteTroupeElite : " << carte_troupe_elite->getPuissance() << " " << carte_troupe_elite->getCouleur() << endl;
        }
        else if (CarteClan * carte_clan = dynamic_cast<CarteClan *>(carte)) {
            cout << i <<"  CarteClan : "  << carte_clan->getPuissance()<< " "<< carte_clan->getCouleur() << endl;

        } else if (CarteTactique * carte_tactique = dynamic_cast<CarteTactique *>(carte)) {
            cout << i <<"  CarteTactique : " << carte_tactique->getNom() << endl;
        }
        i++;
    }
}

void affichage_vecteur_carte2(vector<CarteClan*> v) {   //temporaire juste pour l'affichage dans le main
    for (auto carte: v) {
        if (CarteClan *carte_clan = dynamic_cast<CarteClan *>(carte)) {
            cout << "  CarteClan : " << carte_clan->getPuissance() << " " << carte_clan->getCouleur() << endl;
        }
    }
}