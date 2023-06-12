//
// Created by Utilisateur on 26/04/2023.
//

#include "Plateau.h"
#include "Controleur.h"

void Plateau::poser(Borne borne, CarteClan* carte){
    borne.ajouter_carte(carte);
    //if(m_joueur_actif == 1){
        

        //int fcombi = borne.m_cartesj1->getForceCombi();
        //std::cout << "Force combi : " << fcombi << std::endl;
        //borne.m_cartesj1->ajouterCarte(carte);
        // TODO : ajouter une fonction retirer carte avec cette cate dans la main du joueur
    //}
    //else{
       // int fcombi = borne.m_cartesj2->getForceCombi();
        //std::cout << "Force combi : " << fcombi << std::endl;
        //borne.m_cartesj2->ajouterCarte(carte);
        // TODO : ajouter une fonction retirer carte avec cette cate dans la main du joueur
    //}
    //Controleur::getControleur(true).supprimer_carte_pose_v2(carte);
}

void Plateau::afficherMainJoueur(int joueur) {
    Joueur* joueurcourant= (joueur==1) ? m_joueur1 : m_joueur2;
    vector<Carte*> main = joueurcourant->getMain()->getCartes();
    cout << "Main du joueur " << joueur << ":\n";
    int i=0;
    for (const auto& carte : main) {
        cout << i << ": ";
        carte->afficherCarte();
        i++;
        cout << endl;
    }
    cout << endl;
}

void Plateau::afficherDosMain(int joueur) {
    Joueur* joueurcourant= (joueur==2) ? m_joueur1 : m_joueur2;
    int joueuradverse = (joueur==1) ? 2 : 1;
    vector<Carte*> main = joueurcourant->getMain()->getCartes();

    cout << "Main du joueur " << joueuradverse << ":\n";
    for (const auto& carte : main) {
        carte->afficherDosCarte();
    }
    cout << endl;
}

void Plateau::afficherBornes(int joueur) {
    int joueuradverse = (joueur==1) ? 2 : 1;
    for(int i=0; i<9; i++){
        cout<<"|----------|";
    }
    cout << endl;
    //affichage si revendication Jadverse
    for(int i=0; i<9; i++){
        if(m_bornes[i]->getRevendique()==joueuradverse){
            cout<<"| B"<<i+1<<" revJ"<<joueuradverse<<" |";
        }
        else{
            cout<<"|          |";
        }
    }
    cout << endl;

    //affichage cartes Jadverse
    for(int c=0; c<4; c++){
        for(int i=0; i<9; i++){
            if(joueuradverse==1){
                if(m_bornes[i]->getCartesJ1()->getCartes().size()>c){
                    m_bornes[i]->getCartesJ1()->getCartes()[c]->afficherCarte();
                }
                else{
                    cout<<"|          |";
                }
            }
            else{
                if(m_bornes[i]->getCartesJ2()->getCartes().size()>c){
                    m_bornes[i]->getCartesJ2()->getCartes()[c]->afficherCarte();
                }
                else{
                    cout<<"|          |";
                }
            }
        }
        cout << endl;
    }

    //Affichage bornes centre
    for(int i=0; i<9; i++){
        cout<<"|----------|";
    }
    cout << endl;
    //si collin maillard
    for(int i=0; i<9; i++){
        if(m_bornes[i]->getCartesJ1()->getCollin()){
            cout<<"|  Collin  |";
        }
        else{
            cout<<"|          |";
        }
    }
    cout << endl;
    //affichage numero de borne
    for(int i=0; i<9; i++){
        cout<<"| Borne  "<<i<<" |";
    }
    cout << endl;
    //si combat de boue
    for(int i=0; i<9; i++){
        if(m_bornes[i]->getCartesJ1()->getBoue()){
            cout<<"|   Boue   |";
        }
        else{
            cout<<"|          |";
        }
    }
    cout << endl;
    for(int i=0; i<9; i++){
        cout<<"|----------|";
    }
    cout << endl;

    //affichage cartes Jcourant
    for(int c=0; c<4; c++){
        for(int i=0; i<9; i++){
            if(joueur == 1){
                if(m_bornes[i]->getCartesJ1()->getCartes().size()>c){
                    m_bornes[i]->getCartesJ1()->getCartes()[c]->afficherCarte();
                }
                else{
                    cout<<"|          |";
                }
            }
            else{
                if(m_bornes[i]->getCartesJ2()->getCartes().size()>c){
                    m_bornes[i]->getCartesJ2()->getCartes()[c]->afficherCarte();
                }
                else{
                    cout<<"|          |";
                }
            }
        }
        cout << endl;
    }

    //affichage si revendication Jcourant
    for(int i=0; i<9; i++){
        if(m_bornes[i]->getRevendique()==joueur){
            cout<<"| B"<<i+1<<" revJ"<<joueur<<" |";
        }
        else{
            cout<<"|          |";
        }
    }
    cout << endl;
    for(int i=0; i<9; i++){
        cout<<"|----------|";
    }
    cout << endl;
}

void Plateau::afficherPlateau(int pointdevue) {
    if(pointdevue==1){
        afficherDosMain(2);
        afficherBornes(1);
        afficherMainJoueur(1);
    }
    else{
        afficherDosMain(1);
        afficherBornes(2);
        afficherMainJoueur(2);
    }
}