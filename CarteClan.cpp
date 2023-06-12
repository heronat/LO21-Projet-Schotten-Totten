//
// Created by Utilisateur on 19/04/2023.
//

#include "CarteClan.h"



ostream& operator<<(ostream& os, const CarteClan& carteClan) {
    os << "CarteClan :\n\tPuissance : " << carteClan.getPuissance() << "\n\tCouleur : " << carteClan.getCouleur();
    return os;
}
void affichage_vecteur_carteclan(vector<CarteClan*> v){
    for (auto carte: v) {
        cout << " " << carte->getPuissance()<< " "<< carte->getCouleur();
    }

}