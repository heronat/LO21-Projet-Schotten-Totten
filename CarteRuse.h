//
// Created by Utilisateur on 19/04/2023.
//

#ifndef LO21_SCHOTTEN_TOTTEN_CARTERUSE_H
#define LO21_SCHOTTEN_TOTTEN_CARTERUSE_H
#include"CarteTactique.h"

class CarteRuse : public CarteTactique {
public:
    CarteRuse(const string& nom) : CarteTactique(nom)  {};

    static void Jouer_ChasseurdeTete() ;
    static void Jouer_Stratege() ;
    static void Jouer_Banshee() ;
    static void Jouer_Traitre() ;
    static void Jouer_ChasseurdeTeteIA() ;
    static void Jouer_StrategeIA() ;
    static void Jouer_BansheeIA() ;
    static void Jouer_TraitreIA() ;

    void afficherCarte()const override{
        if(getNom()=="Chasseur de Tete"){
            cout<< "| Chas Tete |";
        }
        else if(getNom()=="Stratege"){
            cout<< "| Stratege |";
        }
        else if(getNom()=="Banshee"){
            cout<< "|  Banshee |";
        }
        else if(getNom()=="Traitre"){
            cout<< "|  Traitre |";
        }

    }

    void afficherDosCarte()const override {
        cout << "| Tactique |";
    }
};

#endif //LO21_SCHOTTEN_TOTTEN_CARTERUSE_H
