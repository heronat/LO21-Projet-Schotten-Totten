//
// Created by Utilisateur on 19/04/2023.
//

#include "CarteRuse.h"
#include "Controleur.h"
#include "Main_Joueur.h"
#include <random>

int generateRandomNumber2() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distribution(1, 100);
    return distribution(rng);
}

void Supp_PushCarteClanTactique(){
    vector<Carte*> cartesMain = Controleur::getControleur(true).getPlateau()->getJoueur1()->getMain()->getCartes();
    cout << "Veuillez choisir la carte que vous voulez jouer (son id) :" << endl;
    int choix_carte, nb_tac = 0, nb_clan = 0, nb_total = 0;
    cin >> choix_carte;
    while (choix_carte >= cartesMain.size() || choix_carte < 0) {
        cout << "Vous n'avez pas cette carte, veuillez saisir une carte que vous avez :" << endl;
        cin >> choix_carte;
    }
    vector<Carte*> cartes =  Controleur::getControleur(true).getPlateau()->getJoueur1()->getMain()->getCartes();
    Carte* carte = cartes[choix_carte];

    if (CarteClan* carteClanChoisie = dynamic_cast<CarteClan*>(carte)) {
        Controleur::getControleur(false).getPiocheClan()->push_back(carte);
        Controleur::getControleur(true).getPlateau()->getJoueur1()->getMain()->supprimerCarte(choix_carte);
}
    else {
        Controleur::getControleur(true).getPiocheTactique()->push_back(carte);
        Controleur::getControleur(true).getPlateau()->getJoueur1()->getMain()->supprimerCarte(choix_carte);
    }
}


void Supp_PushCarteClanTactiqueIA(){
    vector<Carte*> cartesMain = Controleur::getControleur(true).getPlateau()->getJoueur2()->getMain()->getCartes();

    int choix_carte, nb_tac = 0, nb_clan = 0, nb_total = 0;
    choix_carte = generateRandomNumber2()%cartesMain.size()+1;
    while (choix_carte >= cartesMain.size() || choix_carte < 0) {
        choix_carte = generateRandomNumber2()%cartesMain.size()+1;
    }
    vector<Carte*> cartes =  Controleur::getControleur(true).getPlateau()->getJoueur2()->getMain()->getCartes();
    Carte* carte = cartes[choix_carte];

    if (CarteClan* carteClanChoisie = dynamic_cast<CarteClan*>(carte)) {
        Controleur::getControleur(false).getPiocheClan()->push_back(carte);
        Controleur::getControleur(true).getPlateau()->getJoueur2()->getMain()->supprimerCarte(choix_carte);
    }
    else {
        Controleur::getControleur(true).getPiocheTactique()->push_back(carte);
        Controleur::getControleur(true).getPlateau()->getJoueur2()->getMain()->supprimerCarte(choix_carte);
    }
}

void CarteRuse::Jouer_ChasseurdeTeteIA(){
    cout << "L'ia a joué la carte Chasseur de tete." << endl;
    int nbCarteClan = generateRandomNumber2()%3+1;
    while (nbCarteClan>3 || nbCarteClan<0){
        nbCarteClan = generateRandomNumber2()%3+1;
    }
    switch(nbCarteClan){
        case 0 : {
            for (int i = 0 ; i<3;i++){
                switch (Controleur::getControleur(true).getPiocheTactique()->quandjepiochejefaisattention()) {
                    case 1: {
                        cout << "L'ia a pioché la carte tactique :" << endl;
                        CarteTactique * a = new CarteTactique(Controleur::getControleur(true).getPiocheTactique()->piocherCarteTactique());
                        Controleur::getControleur(true).getPlateau()->getJoueur2()->getMain()->ajouterCarte(a);
                        cout << a->getNom() << endl;
                        break;
                    }
                    case 2: {
                        cout << "L'ia a pioche la carte Troupe Elite :" << endl;
                        CarteTroupeElite * b = new CarteTroupeElite(Controleur::getControleur(true).getPiocheTactique()->piocherCarteTroupeElite());
                        Controleur::getControleur(true).getPlateau()->getJoueur2()->getMain()->ajouterCarte(b);
                        cout << b->getNom() << endl;
                        break;
                    }
                }
            }
            break;}
        case 1:{
            CarteClan* c11 = new CarteClan(Controleur::getControleur(false).getPiocheClan()->piocherCarteClan());
            cout <<"Carte piochee : "<< c11->getPuissance() <<" "<< c11->getCouleur() << endl;
            for (int i = 0 ; i<2;i++){
                switch (Controleur::getControleur(true).getPiocheTactique()->quandjepiochejefaisattention()) {
                    case 1: {
                        cout << "L'ia a pioché la carte tactique :" << endl;
                        CarteTactique * a = new CarteTactique(Controleur::getControleur(true).getPiocheTactique()->piocherCarteTactique());
                        Controleur::getControleur(true).getPlateau()->getJoueur2()->getMain()->ajouterCarte(a);
                        cout << a->getNom() << endl;
                        break;
                    }
                    case 2: {
                        cout << "L'ia a pioche la carte Troupe Elite :" << endl;
                        CarteTroupeElite * b = new CarteTroupeElite(Controleur::getControleur(true).getPiocheTactique()->piocherCarteTroupeElite());
                        Controleur::getControleur(true).getPlateau()->getJoueur2()->getMain()->ajouterCarte(b);
                        cout << b->getNom() << endl;
                        break;
                    }
                }
            }
            Controleur::getControleur(false).getPlateau()->getJoueur2()->getMain()->ajouterCarte(c11);
            break;}
        case 2: {
            CarteClan *c21 = new CarteClan(Controleur::getControleur(false).getPiocheClan()->piocherCarteClan());
            Controleur::getControleur(false).getPlateau()->getJoueur2()->getMain()->ajouterCarte(c21);
            cout << "Carte piochee : " << c21->getPuissance() << " " << c21->getCouleur() << endl;
            CarteClan *c22 = new CarteClan(Controleur::getControleur(false).getPiocheClan()->piocherCarteClan());
            Controleur::getControleur(false).getPlateau()->getJoueur2()->getMain()->ajouterCarte(c22);
            cout << "Carte piochee : " << c22->getPuissance() << " " << c22->getCouleur() << endl;
            switch (Controleur::getControleur(true).getPiocheTactique()->quandjepiochejefaisattention()) {
                case 1: {
                    cout << "L'ia a pioché la carte tactique :" << endl;
                    CarteTactique * a = new CarteTactique(Controleur::getControleur(true).getPiocheTactique()->piocherCarteTactique());
                    Controleur::getControleur(true).getPlateau()->getJoueur2()->getMain()->ajouterCarte(a);
                    cout << a->getNom() << endl;
                    break;
                }
                case 2: {
                    cout << "L'ia a pioche la carte Troupe Elite :" << endl;
                    CarteTroupeElite * b = new CarteTroupeElite(Controleur::getControleur(true).getPiocheTactique()->piocherCarteTroupeElite());
                    Controleur::getControleur(true).getPlateau()->getJoueur2()->getMain()->ajouterCarte(b);
                    cout << b->getNom() << endl;
                    break;
                }
            }
            break;
        }
        case 3: {
            CarteClan* c31 = new CarteClan(Controleur::getControleur(false).getPiocheClan()->piocherCarteClan());
            Controleur::getControleur(false).getPlateau()->getJoueur2()->getMain()->ajouterCarte(c31);
            cout <<"Carte piochee : "<< c31->getPuissance() <<" "<< c31->getCouleur() << endl;
            CarteClan* c32 = new CarteClan(Controleur::getControleur(false).getPiocheClan()->piocherCarteClan());
            Controleur::getControleur(false).getPlateau()->getJoueur2()->getMain()->ajouterCarte(c32);
            cout <<"Carte piochee : "<< c32->getPuissance() <<" "<< c32->getCouleur() << endl;
            CarteClan* c33 = new CarteClan(Controleur::getControleur(false).getPiocheClan()->piocherCarteClan());
            Controleur::getControleur(false).getPlateau()->getJoueur2()->getMain()->ajouterCarte(c33);
            cout <<"Carte piochee : "<< c33->getPuissance() <<" "<< c33->getCouleur() << endl;
        }
    }

    cout << "Voici votre main actuelle :" << endl;
    Controleur::getControleur(true).getPlateau()->afficherMainJoueur(2);
    Supp_PushCarteClanTactiqueIA();
    cout << "Voici votre main actuelle :" << endl;
    Controleur::getControleur(true).getPlateau()->afficherMainJoueur(2);
    Supp_PushCarteClanTactiqueIA();
}

void CarteRuse::Jouer_StrategeIA() {
     cout << "L'ia a decide de jouer la carte Stratege" << endl;

     int choix_borne, choix_carte;
     choix_borne = rand() % 8 + 1;
     while (Controleur::getControleur(true).getPlateau()->getBornes(
             choix_borne)->getCartesJ2()->getCartes().empty() ||Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getRevendique()!=0) {
            choix_borne = generateRandomNumber2() % 8 + 1;

     }
     auto cartesBornes = Controleur::getControleur(true).getPlateau()->getBornes(
             choix_borne)->getCartesJ2()->getCartes();


     choix_carte = generateRandomNumber2() % cartesBornes.size();
     while (choix_carte > cartesBornes.size() - 1 || choix_carte < 0) {
         choix_carte = generateRandomNumber2() % cartesBornes.size();
     }
     cout << "L'ia a choisi la carte " << choix_carte << " de la borne " << choix_borne << endl;
     auto carte_choisie = Controleur::getControleur(true).getPlateau()->getBornes(
             choix_borne)->getCartesJ2()->getCartes()[choix_carte];

     Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getCartesJ2()->supprimerCarte_Borne(
             choix_carte);
     int choix;
     choix =generateRandomNumber2() % 2 + 1;

     //On pose la carte sur une autre borne
     if (choix == 2) {

         choix_borne = rand() % 8 + 1;
         while(Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getRevendique()!=0 && (choix_borne<0 && choix_borne>8)){
             choix_borne = generateRandomNumber2() % 8 + 1;
         }
         Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getCartesJ2()->ajouterCarte(carte_choisie);
            cout << "L'ia a choisi de poser la carte sur la borne " << choix_borne << endl;
     }
         //On defausse la carte
     else{

         delete carte_choisie;
            cout << "L'ia a choisi de defausser la carte" << endl;

     }
        cout << "Voici les bornes de l'adversaire bornes : " << endl;
        Controleur::getControleur(true).getPlateau()->afficherBornes(2);
}
void CarteRuse::Jouer_BansheeIA() {
    cout << "L'IA a joué la carte Banshee" << endl;
    int choix_borne, choix_carte;
    choix_borne = generateRandomNumber2() % 8 + 1;

    while (Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getCartesJ1()->getCartes().empty() ||
           Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getRevendique() != 0) {
        choix_borne = generateRandomNumber2() % 8 + 1;
    }

    auto cartesBornes = Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getCartesJ1()->getCartes();
    cout << "Quelle carte souhaitez-vous retirer de la borne " << choix_borne << "?" << endl;

    int taille_borne = cartesBornes.size();
    choix_carte = generateRandomNumber2() % taille_borne;

    while (choix_carte >= taille_borne || choix_carte < 0) {
        choix_carte = generateRandomNumber2() % taille_borne;
    }

    auto carte_choisie = cartesBornes[choix_carte];
    cout << "L'IA a choisi d'enlever la carte : " << carte_choisie->getCouleur() << " " << carte_choisie->getPuissance() << " de la borne "<< choix_borne<< endl;
    Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getCartesJ1()->supprimerCarte_Borne(choix_carte);
}
 void CarteRuse::Jouer_TraitreIA() {
     cout << "L'IA a joué la carte traitre" << endl;
     int choix_borne, choix_carte;
     choix_borne = generateRandomNumber2() % 8 + 1;

     while (Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getCartesJ1()->getCartes().empty() ||
            Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getRevendique() != 0) {
         choix_borne = generateRandomNumber2() % 8 + 1;
     }

     auto cartesBornes = Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getCartesJ1()->getCartes();
     cout << "Quelle carte souhaitez-vous retirer de la borne " << choix_borne << "?" << endl;

     int taille_borne = cartesBornes.size();
     choix_carte = generateRandomNumber2() % taille_borne;

     while (choix_carte >= taille_borne || choix_carte < 0) {
         choix_carte = generateRandomNumber2() % taille_borne;
     }

     CarteClan * carte_choisie = cartesBornes[choix_carte];
     cout << "L'IA a choisi d'enlever la carte : " << carte_choisie->getCouleur() << " " << carte_choisie->getPuissance() << " de la borne "<< choix_borne<< endl;
     Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getCartesJ1()->supprimerCarte_Borne(
             choix_carte);


     choix_borne = generateRandomNumber2() % 8 + 1;
     while (Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getCartesJ2()->getCartes().empty() && Controleur::getControleur(true).getPlateau()->getBornes(
             choix_borne)->getRevendique() == 0) {
         choix_borne = generateRandomNumber2() % 8 + 1;
     }
     Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getCartesJ2()->ajouterCarte(carte_choisie);
     Controleur::getControleur(true).getPlateau()->afficherBornes(2);
}


void CarteRuse::Jouer_ChasseurdeTete() {
    cout << "Vous avez joué la carte Chasseur de Tête" << endl;
    cout  << "Veuillez choisir le nombre de carte Clan que vous voulez piocher :" << endl;
    int nbCarteClan;
    cin >> nbCarteClan;
    while (nbCarteClan>3 || nbCarteClan<0){
        cout << "Vous ne pouvez pas piocher plus ou moins de 3 cartes" << endl;
        cout  << "Veuillez d'abord choisir le nombre de carte Clan que vous voulez piocher :" << endl;
        cin >> nbCarteClan;
    }
    switch(nbCarteClan){
        case 0 : {
            for (int i = 0 ; i<3;i++){
            switch (Controleur::getControleur(true).getPiocheTactique()->quandjepiochejefaisattention()) {
                case 1: {
                    cout << "Vous avez pioche la carte tactique :" << endl;
                    CarteTactique * a = new CarteTactique(Controleur::getControleur(true).getPiocheTactique()->piocherCarteTactique());
                    Controleur::getControleur(true).getPlateau()->getJoueur1()->getMain()->ajouterCarte(a);
                    cout << a->getNom() << endl;
                    break;
                }
                case 2: {
                    cout << "Vous avez pioche la carte troupe Elite :" << endl;
                    CarteTroupeElite * b = new CarteTroupeElite(Controleur::getControleur(true).getPiocheTactique()->piocherCarteTroupeElite());
                    Controleur::getControleur(true).getPlateau()->getJoueur1()->getMain()->ajouterCarte(b);
                    cout << b->getNom() << endl;
                    break;
                }
            }
            }
            break;}
        case 1:{
            CarteClan* c11 = new CarteClan(Controleur::getControleur(false).getPiocheClan()->piocherCarteClan());
            cout <<"Carte piochee : "<< c11->getPuissance() <<" "<< c11->getCouleur() << endl;
            Controleur::getControleur(false).getPlateau()->getJoueur1()->getMain()->ajouterCarte(c11);
            for (int i = 0 ; i<2;i++){
                switch (Controleur::getControleur(true).getPiocheTactique()->quandjepiochejefaisattention()) {
                    case 1: {
                        cout << "Vous avez pioche la carte tactique :" << endl;
                        CarteTactique * a = new CarteTactique(Controleur::getControleur(true).getPiocheTactique()->piocherCarteTactique());
                        Controleur::getControleur(true).getPlateau()->getJoueur1()->getMain()->ajouterCarte(a);
                        cout << a->getNom() << endl;
                        break;
                    }
                    case 2: {
                        cout << "Vous avez pioche la carte troupe Elite :" << endl;
                        CarteTroupeElite * b = new CarteTroupeElite(Controleur::getControleur(true).getPiocheTactique()->piocherCarteTroupeElite());
                        Controleur::getControleur(true).getPlateau()->getJoueur1()->getMain()->ajouterCarte(b);
                        cout << b->getNom() << endl;
                        break;
                    }
                }
            }

            break;}
        case 2: {
            CarteClan *c21 = new CarteClan(Controleur::getControleur(false).getPiocheClan()->piocherCarteClan());
            Controleur::getControleur(false).getPlateau()->getJoueur1()->getMain()->ajouterCarte(c21);
            cout << "Carte piochee : " << c21->getPuissance() << " " << c21->getCouleur() << endl;
            CarteClan *c22 = new CarteClan(Controleur::getControleur(false).getPiocheClan()->piocherCarteClan());
            Controleur::getControleur(false).getPlateau()->getJoueur1()->getMain()->ajouterCarte(c22);
            cout << "Carte piochee : " << c22->getPuissance() << " " << c22->getCouleur() << endl;
            switch (Controleur::getControleur(true).getPiocheTactique()->quandjepiochejefaisattention()) {
                case 1: {
                    cout << "Vous avez pioche la carte tactique :" << endl;
                    CarteTactique * a = new CarteTactique(Controleur::getControleur(true).getPiocheTactique()->piocherCarteTactique());
                    Controleur::getControleur(true).getPlateau()->getJoueur1()->getMain()->ajouterCarte(a);
                    cout << a->getNom() << endl;
                    break;
                }
                case 2: {
                    cout << "Vous avez pioche la carte troupe Elite :" << endl;
                    CarteTroupeElite * b = new CarteTroupeElite(Controleur::getControleur(true).getPiocheTactique()->piocherCarteTroupeElite());
                    Controleur::getControleur(true).getPlateau()->getJoueur1()->getMain()->ajouterCarte(b);
                    cout << b->getNom() << endl;
                    break;
                }
            }
            break;
        }
        case 3: {
            CarteClan* c31 = new CarteClan(Controleur::getControleur(false).getPiocheClan()->piocherCarteClan());
            Controleur::getControleur(false).getPlateau()->getJoueur1()->getMain()->ajouterCarte(c31);
            cout <<"Carte piochee : "<< c31->getPuissance() <<" "<< c31->getCouleur() << endl;
            CarteClan* c32 = new CarteClan(Controleur::getControleur(false).getPiocheClan()->piocherCarteClan());
            Controleur::getControleur(false).getPlateau()->getJoueur1()->getMain()->ajouterCarte(c32);
            cout <<"Carte piochee : "<< c32->getPuissance() <<" "<< c32->getCouleur() << endl;
            CarteClan* c33 = new CarteClan(Controleur::getControleur(false).getPiocheClan()->piocherCarteClan());
            Controleur::getControleur(false).getPlateau()->getJoueur1()->getMain()->ajouterCarte(c33);
            cout <<"Carte piochee : "<< c33->getPuissance() <<" "<< c33->getCouleur() << endl;

        }

    }
    cout << "Vous allez maintenant devoir choisir deux cartes que vous allez supprimer de votre main" << endl;
    cout << "Voici votre main actuelle :" << endl;
    Controleur::getControleur(true).getPlateau()->afficherMainJoueur(1);
    Supp_PushCarteClanTactique();
    cout << "Voici votre main actuelle :" << endl;
    Controleur::getControleur(true).getPlateau()->afficherMainJoueur(1);
    Supp_PushCarteClanTactique();
}

void CarteRuse::Jouer_Stratege() {
    cout << "Vous avez joue la carte Stratege" << endl;
    cout << "Voici toutes vos bornes : " << endl;
    Controleur::getControleur(true).getPlateau()->afficherBornes(1);
    cout << "Veuillez choisir une borne non revendiquee appartenant a vous " << endl;
    int choix_borne, choix_carte;
    cin >> choix_borne;
    while (Controleur::getControleur(true).getPlateau()->getBornes(
            choix_borne)->getCartesJ1()->getCartes().empty()) {
        cout << "Vous n'avez pas de cartes sur cette borne, veuillez en choisir une autre : " << endl;
        cin >> choix_borne;
    }
    auto cartesBornes = Controleur::getControleur(true).getPlateau()->getBornes(
            choix_borne)->getCartesJ1()->getCartes();
    for (int i = 0; i < cartesBornes.size(); i++) {
        cout << "id :" << i << " " << cartesBornes[i]->getCouleur() << " " << cartesBornes[i]->getPuissance()
             << endl;
    }
    cout << "Quelle carte souhaitee vous retirer de la borne "<< choix_borne << "?" << endl;
    cin >> choix_carte;
    while (choix_carte > cartesBornes.size() - 1 || choix_carte < 0) {
        cout << "Vous n'avez pas de cartes sur cette borne, veuillez en choisir une autre : " << endl;
        cin >> choix_carte;
    }
    auto carte_choisie = Controleur::getControleur(true).getPlateau()->getBornes(
            choix_borne)->getCartesJ1()->getCartes()[choix_carte];
    cout << "Vous avez choisi la carte : " << carte_choisie->getCouleur() << " " << carte_choisie->getPuissance()
         << endl;
    Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getCartesJ1()->supprimerCarte_Borne(
            choix_carte);
    cout << "Voulez vous vous defausser de la carte ou bien la poser sur une autre borne ? " << endl;
    cout << "1 : Defausser la carte" << endl;
    cout << "2 : Poser la carte sur une autre borne" << endl;
    int choix;
    cin >> choix;
    if (choix == 2) {
    cout << "Sur quelle borne non revendiquee voulez vous placer votre carte ? " << endl;
    cin >> choix_borne;
    while(Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getRevendique()!=0 && choix_borne<0 && choix_borne>8){
        cout << "Vous ne pouvez pas poser de carte sur cette borne, veuillez en choisir une autre : " << endl;
        cin >> choix_borne;
    }
    Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getCartesJ1()->ajouterCarte(carte_choisie);
}
    else{
        cout << "Vous avez defausse la carte "<< carte_choisie->getCouleur() << " " << carte_choisie->getPuissance()<< endl;
        delete carte_choisie;
    }
}


void CarteRuse::Jouer_Traitre() {
    cout << "Vous avez joue la carte Traitre" << endl;
    cout << "Voici les bornes de l'adversaire bornes : " << endl;
    Controleur::getControleur(true).getPlateau()->afficherBornes(1);
    cout << "Veuillez choisir une borne non revendiquee appartenant a l'adversaire " << endl;
    int choix_borne, choix_carte;
    cin >> choix_borne;
    while (Controleur::getControleur(true).getPlateau()->getBornes(
            choix_borne)->getCartesJ2()->getCartes().empty() || Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getRevendique()!=0 ) {
        cout << "L'adversaire  n'a pas de cartes sur cette borne, veuillez en choisir une autre : " << endl;
        cin >> choix_borne;
    }
    auto cartesBornes = Controleur::getControleur(true).getPlateau()->getBornes(
            choix_borne)->getCartesJ2()->getCartes();
    for (int i = 0; i < cartesBornes.size(); i++) {
        cout << "id :" << i << " " << cartesBornes[i]->getCouleur() << " " << cartesBornes[i]->getPuissance()
             << endl;
    }

    cout << "Quelle carte souhaitee vous retirer de la borne "<< choix_borne << "?" << endl;



    cin >> choix_carte;

    while (choix_carte > cartesBornes.size() - 1 || choix_carte < 0 ) {
        cout << "Vous ne pouvez pas selectionner cette carte, veuillez en choisir une autre : " << endl;
        cin >> choix_carte;
    }
    vector<Carte*> cartesMain = Controleur::getControleur(true).getPlateau()->getJoueur1()->getMain()->getCartes();
    vector<Carte*> cartes = Controleur::getControleur(true).getPlateau()->getJoueur1()->getMain()->getCartes();
    Carte* carte = cartes[choix_carte];
    int a =0;
    while(a==0) {
        if (CarteClan *carteClanChoisie = dynamic_cast<CarteClan *>(carte)) {
            a=1;
            auto carte_choisie = Controleur::getControleur(false).getPlateau()->getBornes(
                    choix_borne)->getCartesJ2()->getCartes()[choix_carte];
            cout << "Vous avez choisi la carte : " << carte_choisie->getCouleur() << " "
                 << carte_choisie->getPuissance()
                 << endl;
            Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getCartesJ2()->supprimerCarte_Borne(
                    choix_carte);
            cout << "Sur quelle borne non revendiquee voulez vous placer votre carte ? " << endl;
            cin >> choix_borne;
            while (Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getRevendique() != 0) {
                cout << "Vous ne pouvez pas poser de carte sur cette borne, veuillez en choisir une autre : " << endl;
                cin >> choix_borne;
            }
            Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getCartesJ1()->ajouterCarte(
                    carte_choisie);
        } else {
            cout << "Vous ne pouvez pas selectionner cette carte, veuillez en choisir une autre : " << endl;
            cin >> choix_carte;

        }
    }



}

void CarteRuse::Jouer_Banshee() {
    cout << "Vous avez joue la carte Banshee" << endl;
    cout << "Voici les bornes de l'adversaire bornes : " << endl;
    Controleur::getControleur(true).getPlateau()->afficherBornes(1);
    cout << "Veuillez choisir une borne non revendiquee appartenant a l'adversaire " << endl;
    int choix_borne, choix_carte;
    cin >> choix_borne;
    while (Controleur::getControleur(true).getPlateau()->getBornes(
            choix_borne)->getCartesJ2()->getCartes().empty() || Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getRevendique()!=0) {
        cout << "L'adversaire  n'a pas de cartes sur cette borne, veuillez en choisir une autre : " << endl;
        cin >> choix_borne;
    }
    auto cartesBornes = Controleur::getControleur(true).getPlateau()->getBornes(
            choix_borne)->getCartesJ2()->getCartes();
    for (int i = 0; i < cartesBornes.size(); i++) {
        cout << "id :" << i << " " << cartesBornes[i]->getCouleur() << " " << cartesBornes[i]->getPuissance()
             << endl;
    }
    cout << "Quelle carte souhaitee vous retirer de la borne "<< choix_borne << "?" << endl;
    cin >> choix_carte;
    while (choix_carte > cartesBornes.size() - 1 || choix_carte < 0) {
        cout << "Vous ne pouvez pas selectionner cette carte, veuillez en choisir une autre : " << endl;
        cin >> choix_carte;
    }
    auto carte_choisie = Controleur::getControleur(true).getPlateau()->getBornes(
            choix_borne)->getCartesJ2()->getCartes()[choix_carte];
    cout << "Vous avez choisi la carte : " << carte_choisie->getCouleur() << " " << carte_choisie->getPuissance()
         << endl;
    Controleur::getControleur(true).getPlateau()->getBornes(choix_borne)->getCartesJ2()->supprimerCarte_Borne(
            choix_carte);

}
