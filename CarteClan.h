//
// Created by Utilisateur on 19/04/2023.
//

#ifndef LO21_SCHOTTEN_TOTTEN_CARTECLAN_H
#define LO21_SCHOTTEN_TOTTEN_CARTECLAN_H
#include"Carte.h"





class CarteClan : public Carte {
    Puissance m_puissance;
    Couleur m_couleur;

public:
    CarteClan(Puissance puissance, Couleur couleur): m_puissance(puissance), m_couleur(couleur) {};
    Puissance getPuissance() const { return m_puissance; }
    Couleur getCouleur() const { return m_couleur; }
    void setCouleur(Couleur couleur) { m_couleur = couleur; }
    void setPuissance(Puissance puissance) { m_puissance = puissance; }

    void afficherCarte()const override {
        switch (getCouleur())
        {
            case Couleur::jaune:
                cout << "| " << getPuissance() << "  " << getCouleur() << " |";
                break;
            case Couleur::vert:
                cout << "| " << getPuissance() << "   " << getCouleur() << " |";
                break;
            case Couleur::violet:
                cout << "| " << getPuissance() << " " << getCouleur() << " |";
                break;
            case Couleur::rouge:
                cout << "| " << getPuissance() << "  " << getCouleur() << " |";
                break;
            case Couleur::bleu:
                cout << "| " << getPuissance() << "   " << getCouleur() << " |";
                break;
            case Couleur::marron:
                cout << "| " << getPuissance() << " " << getCouleur() << " |";
                break;
        }
    }

    void afficherDosCarte()const override {
        cout << "| CarteClan |";
    }
};

ostream &operator<<(ostream &os, const CarteClan &carteClan);
void affichage_vecteur_carteclan(vector<CarteClan*> v);


#endif //LO21_SCHOTTEN_TOTTEN_CARTECLAN_H
