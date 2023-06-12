//
// Created by Utilisateur on 19/04/2023.
//

#include "CarteException.h"

std::initializer_list<Couleur> Couleurs = { Couleur::rouge, Couleur::vert, Couleur::bleu, Couleur::jaune, Couleur::violet, Couleur::marron };
std::initializer_list<Puissance> Puissances = { Puissance::un, Puissance::deux, Puissance::trois, Puissance::quatre, Puissance::cinq, Puissance::six, Puissance::sept, Puissance::huit, Puissance::neuf };

string toString(Couleur c) {
    switch (c) {
        case Couleur::jaune: return "Jaune";
        case Couleur::vert: return "Vert";
        case Couleur::bleu: return "Bleu";
        case Couleur::rouge: return "Rouge";
        case Couleur::violet: return "Violet";
        case Couleur::marron: return "Marron";
        case Couleur::neutre: return "Neutre";
        default: throw CarteException("Couleur inconnue");
    }
}

string toString(Puissance p) {
    switch (p) {
        case Puissance::zero: return "0";
        case Puissance::un: return "1";
        case Puissance::deux: return "2";
        case Puissance::trois: return "3";
        case Puissance::quatre: return "4";
        case Puissance::cinq: return "5";
        case Puissance::six: return "6";
        case Puissance::sept: return "7";
        case Puissance::huit: return "8";
        case Puissance::neuf: return "9";
        default: throw CarteException("Nombre inconnue");
    }
}

ostream& operator<<(ostream& f, Couleur c) { f << toString(c); return f; }
ostream& operator<<(ostream& f, Puissance p) {	f << toString(p); return f; }