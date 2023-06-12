//
// Created by Utilisateur on 24/04/2023.
//

#include "Borne.h"
#include "Controleur.h"

void Borne::ajouter_carte(CarteClan* carte){
    Controleur& c = Controleur::getControleur(true);
    if (c.getPlateau()->getJoueurActif() == 1) {
        m_cartesj1->ajouterCarte(carte);
        if (m_cartesj1->getBoue() == true)
            if (m_cartesj1->getCartes().size() == 4) {
                m_cartesj1->setPremierComplet(1);
                m_cartesj2->setPremierComplet(1);
            }
            else {
                if (m_cartesj1->getCartes().size() == 3) {
                    m_cartesj1->setPremierComplet(1);
                    m_cartesj2->setPremierComplet(1);
                }
            }
    }
    else {
        m_cartesj2->ajouterCarte(carte);
        if (m_cartesj1->getBoue())
            if (m_cartesj1->getPremierComplet() == 0)
                if (m_cartesj1->getCartes().size() == 4) {
                    m_cartesj1->setPremierComplet(2);
                    m_cartesj2->setPremierComplet(2);
                }
                else {
                    if (m_cartesj1->getPremierComplet() == 0)
                        if (m_cartesj1->getCartes().size() == 3) {
                            m_cartesj1->setPremierComplet(2);
                            m_cartesj2->setPremierComplet(2);
                        }
                }
    }

}
