//
// Created by Utilisateur on 19/04/2023.
//

#ifndef LO21_SCHOTTEN_TOTTEN_CARTETROUPEELITE_H
#define LO21_SCHOTTEN_TOTTEN_CARTETROUPEELITE_H
#include "CarteTactique.h"
#include "CarteClan.h"

class CarteTroupeElite : public CarteClan {
    string nom;

public:

    CarteTroupeElite(const string& nom, Puissance puissance, Couleur couleur) : nom(nom), CarteClan( puissance, couleur)  {};

    string getNom() const {
        return nom;
    }

    CarteTroupeElite jouer_Joker() {
        cout << "Carte joker pose : " << endl;
        for (int i = 0; i < 6; i++) {
            cout << i << ": " << static_cast<Couleur>(i) << endl;
        }
        int choix_couleur = -1;
        while (choix_couleur < 0 || choix_couleur > 7) {
            cout << "Veuillez choisir une couleur :" << endl;
            cin >> choix_couleur;
        }
        setCouleur(static_cast<Couleur>(choix_couleur));

        int choix_puissance = -1;
        while (choix_puissance < 0 || choix_puissance > 10) {
            cout << "Veuillez choisir une puissance entre 1 et 9 :" << endl;
            cin >> choix_puissance;
        }
        setPuissance(static_cast<Puissance>(choix_puissance));
    return *this;
    }



    CarteTroupeElite jouer_PorteBouclier()  {
        cout << "Carte Porte Bouclier pose : " << endl;
        for (int i = 0; i < 6; i++) {
            cout << i << ": " << static_cast<Couleur>(i) << endl;
        }
        int choix_couleur = -1;
        while (choix_couleur < 0 || choix_couleur > 7) {
            cout << "Veuillez choisir une couleur :" << endl;
            cin >> choix_couleur;
        }
        setCouleur(static_cast<Couleur>(choix_couleur));

        int choix_puissance = -1;
        while (choix_puissance < 0 || choix_puissance > 4) {
            cout << "Veuillez choisir une puissance entre 1 et 3 :" << endl;
            cin >> choix_puissance;
        }
        setPuissance(static_cast<Puissance>(choix_puissance));
        return *this;
    }
    CarteTroupeElite jouer_Espion() {
        cout << "Carte Espion pose : " << endl;
        for (int i = 0; i < 6; i++) {
            cout << i << ": " << static_cast<Couleur>(i) << endl;
        }
        int choix_couleur = -1;
        while (choix_couleur < 0 || choix_couleur > 7) {
            cout << "Veuillez choisir une couleur :" << endl;
            cin >> choix_couleur;
        }
        setCouleur(static_cast<Couleur>(choix_couleur));
        setPuissance(Puissance::sept);
        return *this;
    }

    void afficherCarte() const override {
        if(getNom()=="Joker"){
            cout << "|    Joker |";
        }
        else if(getNom()=="Porte_Bouclier"){
            cout << "| Prte bou |";
        }
        else if(getNom()=="Espion"){
            cout << "|   Espion |";
        }
        else{
            cout << "|    " << getNom() << "    |";
        }
    }

    void afficherDosCarte() const override {
        cout << "| Tactique |";
    }
};

#endif //LO21_SCHOTTEN_TOTTEN_CARTETROUPEELITE_H
