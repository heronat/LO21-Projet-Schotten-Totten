//
// Created by Utilisateur on 26/04/2023.
//

#include "Controleur.h"
#include "CarteTroupeElite.h"
#include "CarteRuse.h"
#include "CarteModeCombat.h"
#include <ctime>
#include <cstdlib>
#include <random>
#include <sstream>


int generateRandomNumber() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distribution(1, 100);
    return distribution(rng);
}


Controleur::Controleur(bool tactique, bool ia2): m_tactique(tactique), m_gagnant(0), m_jeu_clan(JeuClan::getJeuClan()), m_jeu_tactique(JeuTactique::getJeuTactique()), m_carte_non_pose(m_jeu_clan.getNbCartes())
{
    m_pioche_clan = new Pioche(m_jeu_clan);
    if(tactique){
        m_pioche_tactique = new Pioche(m_jeu_tactique);
        printf("tactique\n");
        m_plateau = new Plateau(7, false, ia2);
    }
    else{
        m_plateau = new Plateau(6, false, ia2);
        printf("classique\n");
    }

    size_t i=0;
    JeuClan::Iterator it=m_jeu_clan.getIterator();
    while (!it.isDone()){
        m_carte_non_pose[i]= new CarteClan(static_cast<const CarteClan&>(it.currentItem()));
        it.next();
        i++;
    }
}

Controleur::~Controleur()
{
    delete m_pioche_clan;
    delete m_pioche_tactique;
    delete m_plateau;
    for(int i=0; i<m_carte_non_pose.size(); i++){
        delete m_carte_non_pose[i];
    }
}

Controleur& Controleur::getControleur(bool tactique, bool ia2)
{
    if (handler.controleur == nullptr)
        handler.controleur = new Controleur(tactique, ia2);
    return *handler.controleur;
}

Controleur& Controleur::getControleur(bool tactique)
{
    if (handler.controleur == nullptr)
        handler.controleur = new Controleur(tactique, false);
    return *handler.controleur;
}

void Controleur::libererControleur()
{
    delete handler.controleur;
    handler.controleur =nullptr;
}

Controleur::Handler Controleur::handler = Handler();


void clean(void)
{
    int c= 0;
    while ( (getchar()) != '\n' && c != EOF);
}

void Controleur::Afficher_Borne1(){
    for(auto i =0; i<9;i++){
        cout << "|B" << i<<":";
        affichage_vecteur_carteclan(m_plateau->getBornes(i)->getCartesJ1()->getCartes());
        cout <<"|"<< endl;
    }
    cout << endl;

}
void Controleur::Afficher_Borne2(){
    for(auto i =0; i<9;i++){
        cout << "|B" << i <<":";
        affichage_vecteur_carteclan(m_plateau->getBornes(i)->getCartesJ2()->getCartes());
        cout <<"|"<< endl;
    }
    cout << endl;
}

void Controleur::afficherCartesNonPose() const
{
    std::cout << "Cartes non posées : " << std::endl;
    for (int i = 0; i < m_carte_non_pose.size(); ++i)
    {
        std::cout << "Carte " << i + 1 << ": ";
        if (m_carte_non_pose[i] != nullptr)
            std::cout << m_carte_non_pose[i]->getCouleur() << " "<< m_carte_non_pose[i]->getPuissance()<< std::endl;
        else
            std::cout << "Aucune carte" << std::endl;
    }
}
void Controleur::JouerTour1(){

   // cout <<"taille pioche clan : "<<getPiocheClan()->getNbCartes()<<"\n";
    //cout <<"taille pioche tactique : "<<getPiocheTactique()->getNbCartes()<<"\n";
    //CarteRuse::Jouer_ChasseurdeTete();
    //cout <<"taille pioche clan : "<<getPiocheClan()->getNbCartes()<<"\n";
    //cout <<"taille pioche tactique : "<<getPiocheTactique()->getNbCartes()<<"\n";
    cout << "Voici votre main :" << endl;
    m_plateau->afficherMainJoueur(1);
    vector<Carte*> cartesMain = m_plateau->m_joueur1->getMain()->getCartes();

    cout << "Veuillez choisir la carte que vous voulez jouer (son id) :" << endl;
    int choix_carte, nb_tac = 0, nb_clan = 0, nb_total = 0;
    cin >> choix_carte;
    clean();
    while (choix_carte >= cartesMain.size() || choix_carte < 0) {
        cout << "Vous n'avez pas cette carte, veuillez saisir une carte que vous avez :" << endl;
        cin >> choix_carte;
    }
    vector<Carte*> cartes = m_plateau->m_joueur1->getMain()->getCartes();
    Carte* carte = cartes[choix_carte];

    if (CarteClan* carteClanChoisie = dynamic_cast<CarteClan*>(carte)) {
        cout << "Vous avez choisi la carte : Puissance :" << carteClanChoisie->getPuissance() << " Couleur : " << carteClanChoisie->getCouleur() << endl;
        m_plateau->afficherBornes(1);
        cout << "Veuillez choisir une borne :" << endl;
        int choix_borne;
        cin >> choix_borne;
        while (choix_borne > 8 || choix_borne < 0) {
            cout << "Vous n'avez pas cette borne, veuillez saisir une borne :" << endl;
            cin >> choix_borne;
        }
        cout << "On pose la carte choisie sur la borne " << choix_borne << " :" << endl;
        m_plateau->poser(*m_plateau->getBornes(choix_borne), carteClanChoisie);
        m_plateau->afficherBornes(1);
        m_plateau->getJoueur1()->getMain()->supprimerCarte(choix_carte);
    }
    else if (CarteTactique* carteTactiqueChoisie = dynamic_cast<CarteTactique*>(carte)) {
        cout << "Vous avez choisi la carte : Nom :" << carteTactiqueChoisie->getNom() << endl;
        cout << "Voulez-vous utiliser cette carte sur quelle borne ? :" << endl;
        if (carteTactiqueChoisie->getNom() == "Colin Maillard") {
            int choix_borne;
            cin >> choix_borne;
            while (choix_borne > 8 || choix_borne < 0) {
                cout << "Vous n'avez pas cette borne, veuillez saisir une borne :" << endl;
                cin >> choix_borne;
            }
            cout << "On pose la carte choisie sur la borne " << choix_borne << " :" << endl;
            CarteModeCombat::jouer_ColinMaillard(m_plateau->getBornes(choix_borne));
        }
        else if (carteTactiqueChoisie->getNom() == "Combat de Boue") {
            int choix_borne;
            cin >> choix_borne;
            while (choix_borne > 8 || choix_borne < 0) {
                cout << "Vous n'avez pas cette borne, veuillez saisir une borne :" << endl;
                cin >> choix_borne;
            }
            cout << "On pose la carte choisie sur la borne " << choix_borne << " :" << endl;
            CarteModeCombat::jouer_CombatdeBoue(m_plateau->getBornes(choix_borne));
        }
        else if (carteTactiqueChoisie->getNom() == "Chasseur de Tete") {
            CarteRuse::Jouer_ChasseurdeTete();
        }
        else if (carteTactiqueChoisie->getNom() == "Stratege") {
            CarteRuse::Jouer_Stratege();
        }
        else if (carteTactiqueChoisie->getNom() == "Banshee") {
            CarteRuse::Jouer_Banshee();
        }
        else if (carteTactiqueChoisie->getNom() == "Traitre") {
            CarteRuse::Jouer_Traitre();
        }
    }
    else if (CarteTroupeElite* carteTroupeEliteChoisie = dynamic_cast<CarteTroupeElite*>(carte)) {
        cout << "Vous avez choisi la carte : Nom :" << carteTroupeEliteChoisie->getNom() << endl;
        cout << "Voulez-vous utiliser cette carte sur quelle borne ? :" << endl;
        int choix_borne;
        cin >> choix_borne;
        while (choix_borne > 8 || choix_borne < 0) {
            cout << "Vous n'avez pas cette borne, veuillez saisir une borne :" << endl;
            cin >> choix_borne;
        }
        cout << "On pose la carte choisie sur la borne " << choix_borne << " :" << endl;
        m_plateau->poser(*m_plateau->getBornes(choix_borne), carteTroupeEliteChoisie);
        cout << "Borne " << choix_borne << " :" << endl;
        affichage_vecteur_carteclan(m_plateau->getBornes(choix_borne)->getCartesJ1()->getCartes());
        cout << endl;

    }
    cout << "Voulez vous revendiquer une borne ? 1 pour oui, 0 pour non :" << endl;
    int choix_revendication;
    cin >> choix_revendication;

    if(choix_revendication==1){
        cout << "Veuillez choisir la borne que vous voulez revendiquer :" << endl;
        int choix_borne;
        cin >> choix_borne;
        while (m_plateau->m_bornes[choix_borne]->getRevendique()==2 || m_plateau->m_bornes[choix_borne]->getRevendique()==1 && (choix_borne > 9 || choix_borne < 1)) {
            cout << "La borne a déjà été revendiquée, veuillez choisir une autre borne :" << endl;
            cin>> choix_borne;
            return;
        }
        revendiquer_borne(choix_borne);
        auto cartesBornes = m_plateau->getBornes(choix_borne)->getCartesJ1()->getCartes();
        int i =0;

    }
    m_plateau->afficherMainJoueur(1);
    cout << "Veuillez choisir si vous voulez choisir une carte tactique ou normale :, 1 pour normale et n'importe qu'elle autre chiffre pour tactique" << endl;
    int choix_style;
    cin >> choix_style;
    cout <<"taille pioche clan : "<<getPiocheClan()->getNbCartes()<<"\n";
    if( int(choix_style)==1 ){
        CarteClan* ci = new CarteClan(getPiocheClan()->piocherCarteClan());
        m_plateau->getJoueur1()->getMain()->ajouterCarte(ci);
        cout <<"Carte piochee : "<< ci->getPuissance() <<" "<< ci->getCouleur() << endl;

    }

    else {
        switch (getPiocheTactique()->quandjepiochejefaisattention()) {
            case 1: {
                cout << "Vous avez pioche la carte tactique :" << endl;
                CarteTactique * a = new CarteTactique(getPiocheTactique()->piocherCarteTactique());
                m_plateau->getJoueur1()->getMain()->ajouterCarte(a);
                cout << a->getNom() << endl;
                break;
            }
            case 2: {
                cout << "Vous avez pioche la carte troupe Elite :" << endl;
                CarteTroupeElite * b = new CarteTroupeElite( getPiocheTactique()->piocherCarteTroupeElite());
                m_plateau->getJoueur1()->getMain()->ajouterCarte(b);
                cout << b->getNom() << endl;
                break;
            }
        }

    }
    //Affichage de la main du joueur 1
    cout << "Votre main est maintenant composee de : " << endl;
    m_plateau->afficherMainJoueur(1);
    cout <<"taille pioche clan : "<<getPiocheClan()->getNbCartes()<<"\n";
    //cout <<"taille pioche tactique : "<<getPiocheTactique()->getNbCartes()<<"\n";
    Afficher_Borne1();
    cout << "\nFIN DU TOUR" << endl;
}

void Controleur::JouerTour2(){

    cout << "Voici votre main :" << endl;
    m_plateau->afficherMainJoueur(2);
    vector<Carte*> cartesMain = m_plateau->m_joueur2->getMain()->getCartes();

    cout << "Veuillez choisir la carte que vous voulez jouer (son id) :" << endl;
    int choix_carte, nb_tac = 0, nb_clan = 0, nb_total = 0;
    cin >> choix_carte;
    clean();
    while (choix_carte >= cartesMain.size() || choix_carte < 0) {
        cout << "Vous n'avez pas cette carte, veuillez saisir une carte que vous avez :" << endl;
        cin >> choix_carte;
    }

    vector<Carte*> cartes = m_plateau->m_joueur2->getMain()->getCartes();
    Carte* carte = cartes[choix_carte];

    if (CarteClan* carteClanChoisie = dynamic_cast<CarteClan*>(carte)) {
        cout << "Vous avez choisi la carte : Puissance :" << carteClanChoisie->getPuissance() << " Couleur : " << carteClanChoisie->getCouleur() << endl;
        m_plateau->afficherBornes(2);
        cout << "Veuillez choisir une borne :" << endl;
        int choix_borne;
        cin >> choix_borne;
        while (choix_borne > 8 || choix_borne < 0) {
            cout << "Vous n'avez pas cette borne, veuillez saisir une borne :" << endl;
            cin >> choix_borne;
        }
        cout << "On pose la carte choisie sur la borne " << choix_borne << " :" << endl;
        m_plateau->poser(*m_plateau->getBornes(choix_borne), carteClanChoisie);
        m_plateau->afficherBornes(2);
        m_plateau->getJoueur2()->getMain()->supprimerCarte(choix_carte);
    }
    else if (CarteTactique* carteTactiqueChoisie = dynamic_cast<CarteTactique*>(carte)) {
        cout << "Vous avez choisi la carte : Nom :" << carteTactiqueChoisie->getNom() << endl;
        cout << "Voulez-vous utiliser cette carte sur quelle borne ? :" << endl;
        if (carteTactiqueChoisie->getNom() == "Colin Maillard") {
            int choix_borne;
            cin >> choix_borne;
            while (choix_borne > 8 || choix_borne < 0) {
                cout << "Vous n'avez pas cette borne, veuillez saisir une borne :" << endl;
                cin >> choix_borne;
            }
            cout << "On pose la carte choisie sur la borne " << choix_borne << " :" << endl;
            CarteModeCombat::jouer_ColinMaillard(m_plateau->getBornes(choix_borne));
        }
        else if (carteTactiqueChoisie->getNom() == "Combat de Boue") {
            int choix_borne;
            cin >> choix_borne;
            while (choix_borne > 8 || choix_borne < 0) {
                cout << "Vous n'avez pas cette borne, veuillez saisir une borne :" << endl;
                cin >> choix_borne;
            }
            cout << "On pose la carte choisie sur la borne " << choix_borne << " :" << endl;
            CarteModeCombat::jouer_CombatdeBoue(m_plateau->getBornes(choix_borne));
        }
        else if (carteTactiqueChoisie->getNom() == "Chasseur de Tete") {
            CarteRuse::Jouer_ChasseurdeTete();
        }
        else if (carteTactiqueChoisie->getNom() == "Stratege") {
            CarteRuse::Jouer_Stratege();
        }
        else if (carteTactiqueChoisie->getNom() == "Banshee") {
            CarteRuse::Jouer_Banshee();
        }
        else if (carteTactiqueChoisie->getNom() == "Traitre") {
            CarteRuse::Jouer_Traitre();
        }
    }
    else if (CarteTroupeElite* carteTroupeEliteChoisie = dynamic_cast<CarteTroupeElite*>(carte)) {
        cout << "Vous avez choisi la carte : Nom :" << carteTroupeEliteChoisie->getNom() << endl;
        cout << "Voulez-vous utiliser cette carte sur quelle borne ? :" << endl;
        int choix_borne;
        cin >> choix_borne;
        while (choix_borne > 8|| choix_borne < 0) {
            cout << "Vous n'avez pas cette borne, veuillez saisir une borne :" << endl;
            cin >> choix_borne;
        }
        cout << "On pose la carte choisie sur la borne " << choix_borne << " :" << endl;
        m_plateau->poser(*m_plateau->getBornes(choix_borne), carteTroupeEliteChoisie);
        cout << "Borne " << choix_borne << " :" << endl;
        affichage_vecteur_carteclan(m_plateau->getBornes(choix_borne)->getCartesJ2()->getCartes());
        cout << endl;

    }
    cout << "Voulez vous revendiquer une borne ? 1 pour oui, 0 pour non :" << endl;
    int choix_revendication;
    cin >> choix_revendication;

    if(choix_revendication==1){
        cout << "Veuillez choisir la borne que vous voulez revendiquer :" << endl;
        int choix_borne;
        cin >> choix_borne;
        while (m_plateau->m_bornes[choix_borne]->getRevendique()==2 || m_plateau->m_bornes[choix_borne]->getRevendique()==1 && (choix_borne > 9 || choix_borne < 1)) {
            cout << "La borne a déjà été revendiquée, veuillez choisir une autre borne :" << endl;
            cin>> choix_borne;
            return;
        }
        revendiquer_borne(choix_borne);
        auto cartesBornes = m_plateau->getBornes(choix_borne)->getCartesJ2()->getCartes();
        int i =0;

    }
    cout << "Veuillez choisir si vous voulez choisir une carte tactique ou normale :, 1 pour normale et n'importe qu'elle autre chiffre pour tactique" << endl;
    int choix_style;
    cin >> choix_style;
    m_plateau->afficherMainJoueur(2);
    cout <<"taille pioche clan : "<<getPiocheClan()->getNbCartes()<<"\n";
    if( int(choix_style)==1 ){
        CarteClan* ci = new CarteClan(getPiocheClan()->piocherCarteClan());
        m_plateau->getJoueur2()->getMain()->ajouterCarte(ci);
        cout <<"Carte piochee : "<< ci->getPuissance() <<" "<< ci->getCouleur() << endl;

    }

    else {
        switch (getPiocheTactique()->quandjepiochejefaisattention()) {
            case 1: {
                cout << "Vous avez pioche la carte tactique :" << endl;
                CarteTactique * a = new CarteTactique(getPiocheTactique()->piocherCarteTactique());
                m_plateau->getJoueur2()->getMain()->ajouterCarte(a);
                cout << a->getNom() << endl;
                break;
            }
            case 2: {
                cout << "Vous avez pioche la carte troupe Elite :" << endl;
                CarteTroupeElite * b = new CarteTroupeElite( getPiocheTactique()->piocherCarteTroupeElite());
                m_plateau->getJoueur2()->getMain()->ajouterCarte(b);
                cout << b->getNom() << endl;
                break;
            }
        }

    }
    //Affichage de la main du joueur 1
    cout << "Votre main est maintenant composee de : " << endl;
    m_plateau->afficherMainJoueur(2);

    cout << "\nFIN DU TOUR" << endl;
}

void Controleur::JouerTourIAClassique(){

    m_plateau->afficherBornes(2);
    m_plateau->afficherMainJoueur(2);
    vector<Carte*> cartesMain = m_plateau->m_joueur1->getMain()->getCartes();
    srand(time(0));
    int choix_carte, nb_tac=0,nb_clan=0,nb_total=0;
    choix_carte = generateRandomNumber()%cartesMain.size();
    while(choix_carte>cartesMain.size() || choix_carte<0){
        cout<<"Vous n'avez pas cette carte, resaisissez une que vous avez :"<<endl;
        choix_carte = generateRandomNumber()%cartesMain.size()+1;
    }
    vector<Carte*> cartes = m_plateau->m_joueur2->getMain()->getCartes();
    Carte* carte = cartes[choix_carte];
    if (carte = dynamic_cast<CarteClan *>(carte)) {
        Carte* carteChoisie = m_plateau->getJoueur2()->getMain()->getCarte(choix_carte);
        CarteClan* carteClanChoisie = dynamic_cast<CarteClan*>(carteChoisie);
            cout << "L'IA a choisi de poser la carte : Puissance :" << carteClanChoisie->getPuissance() << " Couleur : " << carteClanChoisie->getCouleur() << endl;
        //affichage borne
        //Choix de la borne
        int choix_borne = generateRandomNumber()%8+1;
        if (choix_borne > 8|| choix_borne < 0) {
            choix_borne = generateRandomNumber()%8+1;
        }

        while (m_plateau->getBornes(choix_borne)->getCartesJ2()->getCartes().size()==3){
            cout << "La borne est pleine, veuillez choisir une autre borne :" << endl;
            choix_borne = generateRandomNumber()%8+1;
        }


        affichage_vecteur_carteclan(m_plateau->getBornes(choix_borne)->getCartesJ2()->getCartes());cout <<endl;
        cout << "On pose la carte piochee sur la borne "<< choix_borne << " :"<<endl;
        m_plateau->poser(*m_plateau->getBornes(choix_borne),carteClanChoisie );
        cout << "Borne " << choix_borne << " :" << endl;
        affichage_vecteur_carteclan(m_plateau->getBornes(choix_borne)->getCartesJ2()->getCartes());cout <<endl;
        m_plateau->getJoueur2()->getMain()->supprimerCarte(choix_carte);
    }
    m_plateau->afficherBornes(2);
    int count_cartes = 0;
    for (int i=0 ;i <9;i++) {
        count_cartes=0;
        auto cartesBornes = m_plateau->getBornes(i)->getCartesJ2()->getCartes();
            if (cartesBornes.size() ==3) {
                count_cartes = 3;
                revendiquer_borne(i);
                cout << "L'ia a  revendique la borne " << i << endl;
        }
    }

    cout <<"taille pioche clan : "<<getPiocheClan()->getNbCartes()<<"\n";
        CarteClan* ci = new CarteClan(getPiocheClan()->piocherCarteClan());
        m_plateau->getJoueur2()->getMain()->ajouterCarte(ci);
        cout <<"L'ia a piochee la carte  : "<< ci->getPuissance() <<" "<< ci->getCouleur() << endl;
        m_plateau->afficherMainJoueur(1);
    //jouer carte espion
    //Affichage de la main du joueur 1
    cout << "La main de l'IA est maintenant composee de :" << endl;
    m_plateau->afficherMainJoueur(2);
    cout << "\nFIN DU TOUR" << endl;
}



void Controleur::JouerTourIA(){
    m_plateau->afficherBornes(2);


    m_plateau->afficherMainJoueur(2);
    vector<Carte*> cartesMain = m_plateau->m_joueur2->getMain()->getCartes();
    int choix_carte, nb_tac = 0, nb_clan = 0, nb_total = 0;
    choix_carte = generateRandomNumber() % cartesMain.size()+1;
    while (choix_carte >= cartesMain.size() || choix_carte < 0) {
        choix_carte = generateRandomNumber() % cartesMain.size();
    }
    vector<Carte*> cartes = m_plateau->m_joueur2->getMain()->getCartes();
    Carte* carte = cartes[choix_carte];

    if (CarteClan* carteClanChoisie = dynamic_cast<CarteClan*>(carte)) {
        cout << "L'ia a choisie de jouer la carte  : Puissance :" << carteClanChoisie->getPuissance() << " Couleur : " << carteClanChoisie->getCouleur() << endl;
        int choix_borne = generateRandomNumber() % 8 + 1;
        while (choix_borne > 8 || choix_borne < 0) {
            choix_borne = generateRandomNumber() % 8 + 1;
        }
        cout << "L'ia pose sa carte sur la borne " << choix_borne << " :" << endl;
        m_plateau->poser(*m_plateau->getBornes(choix_borne), carteClanChoisie);
        m_plateau->afficherBornes(2);
        m_plateau->getJoueur2()->getMain()->supprimerCarte(choix_carte);
    }
    else if (CarteTactique* carteTactiqueChoisie = dynamic_cast<CarteTactique*>(carte)) {
        cout << "L'ia a choisie la carte : Nom :" << carteTactiqueChoisie->getNom() << endl;
        if (carteTactiqueChoisie->getNom() == "Colin Maillard") {
            int choix_borne = generateRandomNumber() % 8 + 1;

            while (choix_borne > 8 || choix_borne < 0) {
                choix_borne = generateRandomNumber() % 8 + 1;
            }
            cout << "L'IA pose la carte choisie sur la borne " << choix_borne << " :" << endl;
            CarteModeCombat::jouer_ColinMaillard(m_plateau->getBornes(choix_borne));
        }
        else if (carteTactiqueChoisie->getNom() == "Combat de Boue") {
            int choix_borne = generateRandomNumber() % 8 + 1;

            while (choix_borne > 8 || choix_borne < 0) {
                choix_borne = generateRandomNumber() % 8 + 1;
            }
            cout << "L'ia  pose la carte choisie sur la borne " << choix_borne << " :" << endl;
            CarteModeCombat::jouer_CombatdeBoue(m_plateau->getBornes(choix_borne));
        }
        else if (carteTactiqueChoisie->getNom() == "Chasseur de Tete") {
            CarteRuse::Jouer_ChasseurdeTeteIA();
        }
        else if (carteTactiqueChoisie->getNom() == "Stratege") {
            CarteRuse::Jouer_StrategeIA();
        }
        else if (carteTactiqueChoisie->getNom() == "Banshee") {
            CarteRuse::Jouer_BansheeIA();
        }
        else if (carteTactiqueChoisie->getNom() == "Traitre") {
            CarteRuse::Jouer_TraitreIA();
        }
    }
    else if (CarteTroupeElite* carteTroupeEliteChoisie = dynamic_cast<CarteTroupeElite*>(carte)) {
        cout << "L'ia a choisi la carte : Nom :" << carteTroupeEliteChoisie->getNom() << endl;
        int choix_borne = generateRandomNumber() % 8 + 1;
        while (choix_borne > 8|| choix_borne < 0) {
            choix_borne = generateRandomNumber() % 8 + 1;
        }
        cout << "L'ia pose la carte choisie sur la borne " << choix_borne << " :" << endl;
        m_plateau->poser(*m_plateau->getBornes(choix_borne), carteTroupeEliteChoisie);
        cout << "Borne " << choix_borne << " :" << endl;
        affichage_vecteur_carteclan(m_plateau->getBornes(choix_borne)->getCartesJ2()->getCartes());
        cout << endl;

    }
    //L'ia cherche à revendiquer les bornes où elle a 3 cartes
    int count_cartes = 0;
    for (int i=0 ;i <9;i++) {
        count_cartes=0;
        auto cartesBornes = m_plateau->getBornes(i)->getCartesJ1()->getCartes();
        if (cartesBornes.size() ==3 ||cartesBornes.size()==4) {
            cout << "L'ia va tenter de  revendiquer la borne " << i << endl;
            revendiquer_borne(i);

        }
    }
    int choix_style = generateRandomNumber()%2+1;

    if( int(choix_style)==1 ){
        CarteClan* ci = new CarteClan(getPiocheClan()->piocherCarteClan());
        m_plateau->getJoueur2()->getMain()->ajouterCarte(ci);
        cout <<"L'ia a pioche la carte  : "<< ci->getPuissance() <<" "<< ci->getCouleur() << endl;
        m_plateau->afficherMainJoueur(2);
    }
    else {
        switch (getPiocheTactique()->quandjepiochejefaisattention()) {
            case 1: {
                cout << "L'ia a pioche  la carte tactique :" << endl;
                CarteTactique * a = new CarteTactique(getPiocheTactique()->piocherCarteTactique());
                m_plateau->getJoueur2()->getMain()->ajouterCarte(a);
                cout << a->getNom() << endl;
                break;
            }
            case 2: {
                cout << "L'ia a pioche la carte troupe Elite :" << endl;
                CarteTroupeElite * b = new CarteTroupeElite( getPiocheTactique()->piocherCarteTroupeElite());
                m_plateau->getJoueur2()->getMain()->ajouterCarte(b);
                cout << b->getNom() << endl;
                break;
            }
        }

    }
    //Affichage de la main du joueur 1

    cout << "\nFIN DU TOUR" << endl;


}






bool Controleur::check_fin_partie() {
    int sum1=0;
    int serie1=0;
    int sum2=0;
    int serie2=0;
    for(auto i=0; i<9; i++){
        int j = m_plateau->m_bornes[i]->getRevendique();
        //printf("test");
        if(j==1){
            sum1++;
            serie1++;
            //printf("test1");
            if(serie1==3){
                m_gagnant=1;
                //printf("test3");
                return true;
            }
            serie2=0;
        }
        else if(j==2){
            sum2++;
            serie2++;
            //printf("test2");
            if(serie2==3){
                m_gagnant=2;
                return true;
            }
            serie1=0;
        }
        else {
            serie1=0;
            serie2=0;
        }
        if (sum1 == 5){
            m_gagnant=1;
            return true;
        }
        else if (sum2 == 5){
            m_gagnant=2;
            return true;
        }
    }
    return false;
}

std::string Controleur::revendiquer_borne(int num_borne) {

    Borne *borne = m_plateau->getBornes(num_borne);
    Combinaison *combi_j1 = borne->getCartesJ1();
    Combinaison *combi_j2 = borne->getCartesJ2();
    vector<CarteClan *> cartes_pose_j1 = combi_j1->getCartes();
    vector<CarteClan *> cartes_pose_j2 = combi_j2->getCartes();

    //TODO temporaire:
    cout << "Les cartes sont\nJ1:  "<< endl;
    affichage_vecteur_carteclan(cartes_pose_j1);
    cout << "\nJ2:" << endl;
    affichage_vecteur_carteclan(cartes_pose_j2);
    cout <<"\n"<<endl;

    int joueur_qui_revendique = getPlateau()->getJoueurActif();
    if (joueur_qui_revendique == 1){
        if(combi_j1->getBoue() == 0){
            if (cartes_pose_j1.size() !=3){
                return "J1 n'a pas pose 3 cartes, il ne peut pas revendiquer la borne";
            }
        }
        else{
            if (cartes_pose_j1.size() !=4){
                return "J1 n'a pas pose 4 cartes, il ne peut pas revendiquer la borne";
            }
        }
    }
    else{
        if(combi_j2->getBoue() == 0){
            if (cartes_pose_j2.size() !=3){
                return "J2 n'a pas pose 3 cartes, il ne peut pas revendiquer la borne";
            }
        }
        else{
            if (cartes_pose_j2.size() !=4){
                return "J2 n'a pas pose 4 cartes, il ne peut pas revendiquer la borne";
            }
        }
    }

    if (joueur_qui_revendique == 1) {
        cout << "J1 revendique la borne "<< num_borne << endl;

        if (il_y_a_joker(cartes_pose_j1) || il_y_a_portebou(cartes_pose_j1) || il_y_a_espion(cartes_pose_j1)) {
            //Si on a des cartes troupes d'elite alors J1 choisi leur valeur
            for (auto c: cartes_pose_j1) {
                if (auto t = dynamic_cast<CarteTroupeElite *>(c)) {
                    auto nom = t->getNom();
                    if (nom == "Joker") {
                        //t->jouer_Joker();
                        combi_j1->calculerForceCombi();
                        combi_j1->setTotalPuissance(combi_j1->getTotalPuissance() + static_cast<int>(t->getPuissance()));
                    } else if (nom == "Espion") {
                        //t->jouer_Espion();
                        combi_j1->calculerForceCombi();
                        combi_j1->setTotalPuissance(combi_j1->getTotalPuissance() + static_cast<int>(t->getPuissance()));

                    } else if (nom == "Porte_Bouclier") {
                        //t->jouer_PorteBouclier();
                        combi_j1->calculerForceCombi();
                        combi_j1->setTotalPuissance(combi_j1->getTotalPuissance() + static_cast<int>(t->getPuissance()));

                    }
                }
            }
        }

        int tab_troupe_tac[4] = {0, 0, 0, 0};
        if (il_y_a_joker(cartes_pose_j2) || il_y_a_portebou(cartes_pose_j2) || il_y_a_espion(cartes_pose_j2)) {
            // J2 a posé des carte troupe d'elite mais J1 revendique : on teste tt les valeurs possible que peuvent prendre les cartes de J2
            size_t i = 0;
            for (auto c: cartes_pose_j2) {
                if (auto t = dynamic_cast<CarteTroupeElite *>(c)) {
                    auto nom = t->getNom();
                    if (nom == "Joker") {
                        tab_troupe_tac[i] = 1;
                    } else if (nom == "Espion") {
                        tab_troupe_tac[i] = 2;
                    } else if (nom == "Porte_Bouclier") {
                        tab_troupe_tac[i] = 3;
                    }
                }
                i++;
            }
        }
        if (combi_j1->getBoue() == 0) {
            // creation des vecteur sur les quels les cartes de J2 vont varier
            vector<CarteClan *> cartes_a1 = m_carte_non_pose;
            vector<CarteClan *> cartes_a2 = m_carte_non_pose;
            vector<CarteClan *> cartes_a3 = m_carte_non_pose;
            if (cartes_pose_j2.size()) {
                for (auto i = 0; i < cartes_pose_j2.size() ; i++)
                    switch (i) {
                    case (0): {
                        switch (tab_troupe_tac[i]) {
                        case (0): {
                            cartes_a1.clear();
                            cartes_a1.push_back(cartes_pose_j2[i]);
                            break;
                        }
                        case (1): {
                            cartes_a1.clear();
                            cartes_a1 = gen_vect_joker();
                            break;
                        }
                        case (2): {
                            cartes_a1.clear();
                            cartes_a1 = gen_vect_espion();
                            break;
                        }
                        case (3): {
                            cartes_a1.clear();
                            cartes_a1 = gen_vect_portebou();
                            break;
                        }
                        }
                        break;
                    }
                    case (1): {
                        switch (tab_troupe_tac[i]) {
                        case (0): {
                            cartes_a2.clear();
                            cartes_a2.push_back(cartes_pose_j2[i]);
                            break;
                        }
                        case (1): {
                            cartes_a2.clear();
                            cartes_a2 = gen_vect_joker();
                            break;
                        }
                        case (2): {
                            cartes_a2.clear();
                            cartes_a2 = gen_vect_espion();
                            break;
                        }
                        case (3): {
                            cartes_a2.clear();
                            cartes_a2 = gen_vect_portebou();
                            break;
                        }
                        }
                        break;
                    }
                    case (2): {
                        switch (tab_troupe_tac[i]) {
                        case (0): {
                            cartes_a3.clear();
                            cartes_a3.push_back(cartes_pose_j2[i]);
                            break;
                        }
                        case (1): {
                            cartes_a3.clear();
                            cartes_a3 = gen_vect_joker();
                            break;
                        }
                        case (2): {
                            cartes_a3.clear();
                            cartes_a3 = gen_vect_espion();
                            break;
                        }
                        case (3): {
                            cartes_a3.clear();
                            cartes_a3 = gen_vect_portebou();
                            break;
                        }
                        }
                        break;
                    }
                    }
            }

            for (auto a1: cartes_a1) {
                for (auto a2: cartes_a2) {
                    for (auto a3: cartes_a3) {
                        if (CarteClan_egales(a1, a2) || CarteClan_egales(a1, a3) ||
                            CarteClan_egales(a2, a3)  )
                            continue;

                        Combinaison *combi_temp = new Combinaison();
                        combi_temp->ajouterCarte(a1);
                        combi_temp->ajouterCarte(a2);
                        combi_temp->ajouterCarte(a3);
                        if (qui_gagne(combi_j1, combi_temp) == 2) {
                            // J2 gagne
                            std::ostringstream oss;
                            oss << "\nECHEC J2 peut gagner: " << endl;
                            oss << a1->getPuissance() <<" "<< a1->getCouleur() << " "<< a2->getPuissance() <<" "<< a2->getCouleur() << " "<< a3->getPuissance() <<" "<< a3->getCouleur() << endl;
                            delete combi_temp;
                            return oss.str();
                        }

                    }
                }
            }
            std::ostringstream oss;
            oss << "REUSSITE: J2 ne peut pas gagner (J1 gagne)" << endl;
            borne->setRevendique(1);
            return oss.str();
        }
        else {
            vector<CarteClan *> cartes_a1 = m_carte_non_pose;
            vector<CarteClan *> cartes_a2 = m_carte_non_pose;
            vector<CarteClan *> cartes_a3 = m_carte_non_pose;
            vector<CarteClan *> cartes_a4 = m_carte_non_pose;
            if (cartes_pose_j2.size()) {
                for (auto i = 0; i < cartes_pose_j2.size() ; i++)
                    switch (i) {
                    case (0): {
                        switch (tab_troupe_tac[i]) {
                        case (0): {
                            cartes_a1.clear();
                            cartes_a1.push_back(cartes_pose_j2[i]);
                            break;
                        }
                        case (1): {
                            cartes_a1.clear();
                            cartes_a1 = gen_vect_joker();
                            break;
                        }
                        case (2): {
                            cartes_a1.clear();
                            cartes_a1 = gen_vect_espion();
                            break;
                        }
                        case (3): {
                            cartes_a1.clear();
                            cartes_a1 = gen_vect_portebou();
                            break;
                        }
                        }
                        break;
                    }
                    case (1): {
                        switch (tab_troupe_tac[i]) {
                        case (0): {
                            cartes_a2.clear();
                            cartes_a2.push_back(cartes_pose_j2[i]);
                            break;
                        }
                        case (1): {
                            cartes_a2.clear();
                            cartes_a2 = gen_vect_joker();
                            break;
                        }
                        case (2): {
                            cartes_a2.clear();
                            cartes_a2 = gen_vect_espion();
                            break;
                        }
                        case (3): {
                            cartes_a2.clear();
                            cartes_a2 = gen_vect_portebou();
                            break;
                        }
                        }
                        break;
                    }
                    case (2): {
                        switch (tab_troupe_tac[i]) {
                        case (0): {
                            cartes_a3.clear();
                            cartes_a3.push_back(cartes_pose_j2[i]);
                            break;
                        }
                        case (1): {
                            cartes_a3.clear();
                            cartes_a3 = gen_vect_joker();
                            break;
                        }
                        case (2): {
                            cartes_a3.clear();
                            cartes_a3 = gen_vect_espion();
                            break;
                        }
                        case (3): {
                            cartes_a3.clear();
                            cartes_a3 = gen_vect_portebou();
                            break;
                        }
                        }
                        break;
                    }
                    case (3): {
                        switch (tab_troupe_tac[i]) {
                        case (0): {
                            cartes_a4.clear();
                            cartes_a4.push_back(cartes_pose_j2[i]);
                            break;
                        }
                        case (1): {
                            cartes_a4.clear();
                            cartes_a4 = gen_vect_joker();
                            break;
                        }
                        case (2): {
                            cartes_a4.clear();
                            cartes_a4 = gen_vect_espion();
                            break;
                        }
                        case (3): {
                            cartes_a4.clear();
                            cartes_a4 = gen_vect_portebou();
                            break;
                        }
                        }
                        break;
                    }
                    }
            }
            for (auto a1: cartes_a1) {
                for (auto a2: cartes_a2) {
                    for (auto a3: cartes_a3) {
                        for (auto a4: cartes_a4) {
                            if (CarteClan_egales(a1, a2) || CarteClan_egales(a1, a3) || CarteClan_egales(a1, a4) ||
                                CarteClan_egales(a2, a3) || CarteClan_egales(a2, a4) || CarteClan_egales(a3, a4))
                                continue;
                            Combinaison *combi_temp = new Combinaison();
                            combi_temp->setBoue(true);
                            combi_temp->ajouterCarte(a1);
                            combi_temp->ajouterCarte(a2);
                            combi_temp->ajouterCarte(a3);
                            combi_temp->ajouterCarte(a4);
                            if (qui_gagne(combi_j1, combi_temp) == 2) {
                                // J2 gagne
                                std::ostringstream oss;
                                oss << "ECHEC J2 peut gagner" << endl;
                                oss << a1->getPuissance() <<" "<< a1->getCouleur() << " "<< a2->getPuissance() <<" "<< a2->getCouleur() << " "<< a3->getPuissance() <<" "<< a3->getCouleur() << " "<< a4->getPuissance() <<" "<< a4->getCouleur() << endl;
                                delete combi_temp;
                                return oss.str();

                            }
                        }
                    }
                }
            }
            std::ostringstream oss;
            oss << "REUSSITE J2 ne peut pas gagner (J1 gagne 2)" << endl;
            borne->setRevendique(1);
            return oss.str();
        }
    }
    else {
        // J2 revendique
        cout << "J2 revendique la borne "<< num_borne << endl;
        if(il_y_a_joker(cartes_pose_j2) || il_y_a_espion(cartes_pose_j2) || il_y_a_portebou(cartes_pose_j2)){
            for (auto c: cartes_pose_j2) {
                if (auto t = dynamic_cast<CarteTroupeElite *>(c)) {
                    auto nom = t->getNom();
                    if (nom == "Joker") {
                        //t->jouer_Joker();
                        combi_j2->calculerForceCombi();
                        combi_j2->setTotalPuissance(combi_j2->getTotalPuissance() + static_cast<int>(t->getPuissance()));

                    } else if (nom == "Espion") {
                        //t->jouer_Espion();
                        combi_j2->calculerForceCombi();
                        combi_j2->setTotalPuissance(combi_j2->getTotalPuissance() + static_cast<int>(t->getPuissance()));

                    } else if (nom == "Porte_Bouclier") {
                        //t->jouer_PorteBouclier();
                        combi_j2->calculerForceCombi();
                        combi_j2->setTotalPuissance(combi_j2->getTotalPuissance() + static_cast<int>(t->getPuissance()));

                    }
                }
            }

        }
        int tab_troupe_tac[4] = {0, 0, 0, 0};
        if (il_y_a_joker(cartes_pose_j1) || il_y_a_portebou(cartes_pose_j1) || il_y_a_espion(cartes_pose_j1)) {
            size_t i = 0;
            for (auto c: cartes_pose_j1) {
                if (auto t = dynamic_cast<CarteTroupeElite *>(c)) {
                    auto nom = t->getNom();
                    if (nom == "Joker") {
                        tab_troupe_tac[i] = 1;
                    } else if (nom == "Espion") {
                        tab_troupe_tac[i] = 2;
                    } else if (nom == "Porte_Bouclier") {
                        tab_troupe_tac[i] = 3;
                    }
                }
                i++;
            }
        }
        if (combi_j2->getBoue() == 0) {
            vector<CarteClan *> cartes_a1 = m_carte_non_pose;
            vector<CarteClan *> cartes_a2 = m_carte_non_pose;
            vector<CarteClan *> cartes_a3 = m_carte_non_pose;
            if (cartes_pose_j1.size()) {
                for (auto i = 0; i < cartes_pose_j1.size(); i++)
                    switch (i) {
                    case (0): {
                        switch (tab_troupe_tac[i]) {
                        case (0): {
                            cartes_a1.clear();
                            cartes_a1.push_back(cartes_pose_j2[i]);
                            break;
                        }
                        case (1): {
                            cartes_a1.clear();
                            cartes_a1 = gen_vect_joker();
                            break;
                        }
                        case (2): {
                            cartes_a1.clear();
                            cartes_a1 = gen_vect_espion();
                            break;
                        }
                        case (3): {
                            cartes_a1.clear();
                            cartes_a1 = gen_vect_portebou();
                            break;
                        }
                        }
                        break;
                    }
                    case (1): {
                        switch (tab_troupe_tac[i]) {
                        case (0): {
                            cartes_a2.clear();
                            cartes_a2.push_back(cartes_pose_j2[i]);
                            break;
                        }
                        case (1): {
                            cartes_a2.clear();
                            cartes_a2 = gen_vect_joker();
                            break;
                        }
                        case (2): {
                            cartes_a2.clear();
                            cartes_a2 = gen_vect_espion();
                            break;
                        }
                        case (3): {
                            cartes_a2.clear();
                            cartes_a2 = gen_vect_portebou();
                            break;
                        }
                        }
                        break;
                    }
                    case (2): {
                        switch (tab_troupe_tac[i]) {
                        case (0): {
                            cartes_a3.clear();
                            cartes_a3.push_back(cartes_pose_j2[i]);
                            break;
                        }
                        case (1): {
                            cartes_a3.clear();
                            cartes_a3 = gen_vect_joker();
                            break;
                        }
                        case (2): {
                            cartes_a3.clear();
                            cartes_a3 = gen_vect_espion();
                            break;
                        }
                        case (3): {
                            cartes_a3.clear();
                            cartes_a3 = gen_vect_portebou();
                            break;
                        }
                        }
                        break;
                    }
                    }
            }

            for (auto a1: cartes_a1) {
                for (auto a2: cartes_a2) {
                    for (auto a3: cartes_a3) {
                        if (CarteClan_egales(a1, a2) || CarteClan_egales(a1, a3) ||
                            CarteClan_egales(a2, a3) )
                            continue;
                        Combinaison *combi_temp = new Combinaison();
                        combi_temp->ajouterCarte(a1);
                        combi_temp->ajouterCarte(a2);
                        combi_temp->ajouterCarte(a3);
                        if (qui_gagne(combi_j2, combi_temp) == 2) {
                            // J1 gagne
                            std::ostringstream oss;
                            oss << "\nECHEC J1 peut gagner: " << endl;
                            oss << a1->getPuissance() <<" "<< a1->getCouleur() << " "<< a2->getPuissance() <<" "<< a2->getCouleur() << " "<< a3->getPuissance() <<" "<< a3->getCouleur() << endl;
                            delete combi_temp;
                            return oss.str();
                        }
                    }
                }
            }
            std::ostringstream oss;
            oss << "REUSSITE J1 ne peut pas gagner (J2 gagne 1)" << endl;
            borne->setRevendique(2);
            return oss.str();
        }
        else {
            vector<CarteClan *> cartes_a1 = m_carte_non_pose;
            vector<CarteClan *> cartes_a2 = m_carte_non_pose;
            vector<CarteClan *> cartes_a3 = m_carte_non_pose;
            vector<CarteClan *> cartes_a4 = m_carte_non_pose;
            if (cartes_pose_j1.size()) {
                for (auto i = 0; i < cartes_pose_j1.size() ; i++)
                    switch (i) {
                    case (0): {
                        switch (tab_troupe_tac[i]) {
                        case (0): {
                            cartes_a1.clear();
                            cartes_a1.push_back(cartes_pose_j2[i]);
                            break;
                        }
                        case (1): {
                            cartes_a1.clear();
                            cartes_a1 = gen_vect_joker();
                            break;
                        }
                        case (2): {
                            cartes_a1.clear();
                            cartes_a1 = gen_vect_espion();
                            break;
                        }
                        case (3): {
                            cartes_a1.clear();
                            cartes_a1 = gen_vect_portebou();
                            break;
                        }
                        }
                        break;
                    }
                    case (1): {
                        switch (tab_troupe_tac[i]) {
                        case (0): {
                            cartes_a2.clear();
                            cartes_a2.push_back(cartes_pose_j2[i]);
                            break;
                        }
                        case (1): {
                            cartes_a2.clear();
                            cartes_a2 = gen_vect_joker();
                            break;
                        }
                        case (2): {
                            cartes_a2.clear();
                            cartes_a2 = gen_vect_espion();
                            break;
                        }
                        case (3): {
                            cartes_a2.clear();
                            cartes_a2 = gen_vect_portebou();
                            break;
                        }
                        }
                        break;
                    }
                    case (2): {
                        switch (tab_troupe_tac[i]) {
                        case (0): {
                            cartes_a3.clear();
                            cartes_a3.push_back(cartes_pose_j2[i]);
                            break;
                        }
                        case (1): {
                            cartes_a3.clear();
                            cartes_a3 = gen_vect_joker();
                            break;
                        }
                        case (2): {
                            cartes_a3.clear();
                            cartes_a3 = gen_vect_espion();
                            break;
                        }
                        case (3): {
                            cartes_a3.clear();
                            cartes_a3 = gen_vect_portebou();
                            break;
                        }
                        }
                        break;
                    }
                    case (3): {
                        switch (tab_troupe_tac[i]) {
                        case (0): {
                            cartes_a4.clear();
                            cartes_a4.push_back(cartes_pose_j2[i]);
                            break;
                        }
                        case (1): {
                            cartes_a4.clear();
                            cartes_a4 = gen_vect_joker();
                            break;
                        }
                        case (2): {
                            cartes_a4.clear();
                            cartes_a4 = gen_vect_espion();
                            break;
                        }
                        case (3): {
                            cartes_a4.clear();
                            cartes_a4 = gen_vect_portebou();
                            break;
                        }
                        }
                        break;
                    }
                    }
            }
            for (auto a1: cartes_a1) {
                for (auto a2: cartes_a2) {
                    for (auto a3: cartes_a3) {
                        for (auto a4: cartes_a4) {
                            if (CarteClan_egales(a1, a2) || CarteClan_egales(a1, a3) || CarteClan_egales(a1, a4) ||
                                CarteClan_egales(a2, a3) || CarteClan_egales(a2, a4) || CarteClan_egales(a3, a4))
                                continue;
                            Combinaison *combi_temp = new Combinaison();
                            combi_temp->setBoue(true);
                            combi_temp->ajouterCarte(a1);
                            combi_temp->ajouterCarte(a2);
                            combi_temp->ajouterCarte(a3);
                            combi_temp->ajouterCarte(a4);
                            if (qui_gagne(combi_j2, combi_temp) == 2) {
                                // J1 gagne
                                std::ostringstream oss;
                                oss << "ECHEC J1 peut gagner" << endl;
                                oss << a1->getPuissance() <<" "<< a1->getCouleur() << " "<< a2->getPuissance() <<" "<< a2->getCouleur()  << " "<< a3->getPuissance() <<" "<< a3->getCouleur() << " "<< a4->getPuissance() <<" "<< a4->getCouleur() << endl;
                                delete combi_temp;
                                return oss.str();
                            }
                        }
                    }
                }
            }
            std::ostringstream oss;
            oss << "REUSSITE J1 ne peut pas gagner (J2 gagne 2)" << endl;
            borne->setRevendique(2);
            return oss.str();
        }
    }
}

void Controleur::fin_de_partie(){

    delete m_plateau->m_joueur1;
    delete m_plateau->m_joueur2;


    // Libérer la mémoire des objets membres des différentes classes
    delete[] m_plateau->m_joueur1->getMain();
    delete[] m_plateau->m_joueur2->getMain();

    // Vider et supprimer les conteneurs de pointeurs
    vector<Carte*> cartesMain1 = m_plateau->m_joueur1->getMain()->getCartes();
    for (int i = 0; i < cartesMain1.size(); i++) {
        delete cartesMain1[i];
    }
    cartesMain1.clear();

    vector<Carte*> cartesMain2 = m_plateau->m_joueur2->getMain()->getCartes();
    for (int i = 0; i < cartesMain2.size(); i++) {
        delete cartesMain2[i];
    }
    cartesMain2.clear();
    for (int i=0;i<9;i++){
        delete m_plateau->m_bornes[i];
    }
    delete m_plateau;

    delete m_pioche_clan;
    if (m_tactique) {
        delete m_pioche_tactique;
    }
    for (auto carte : m_carte_non_pose){
        delete carte;
    }
    m_carte_non_pose.clear();
}

void Controleur::debut_de_partie_classique() {
    // Ajout des 6 cartes dans la main du joueur 1
    if(m_tactique){
        for (int i = 0; i < 7; i++) {
            CarteClan *ci = new CarteClan(getPiocheClan()->piocherCarteClan());
            m_plateau->m_joueur1->getMain()->ajouterCarte(ci);
        }

        // Ajout des 6 cartes dans la main du joueur 2
        for (int i = 0; i < 7; i++) {
            CarteClan *ci = new CarteClan(getPiocheClan()->piocherCarteClan());
            m_plateau->m_joueur2->getMain()->ajouterCarte(ci);
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            CarteClan *ci = new CarteClan(getPiocheClan()->piocherCarteClan());
            m_plateau->m_joueur1->getMain()->ajouterCarte(ci);
        }

        // Ajout des 6 cartes dans la main du joueur 2
        for (int i = 0; i < 6; i++) {
            CarteClan *ci = new CarteClan(getPiocheClan()->piocherCarteClan());
            m_plateau->m_joueur2->getMain()->ajouterCarte(ci);
        }
    }


    // Affichage des mains des joueurs
    m_plateau->afficherMainJoueur(1);
    m_plateau->afficherMainJoueur(2);
    cout << "Fin de la phase de pioche" << endl<<endl;
}

void Controleur::debut_de_partie_tactique() {
    // Ajout des 7 cartes dans la main du joueur 1
    for (int i = 0; i < 7; i++) {
        CarteClan *ci = new CarteClan(getPiocheClan()->piocherCarteClan());
        m_plateau->m_joueur1->getMain()->ajouterCarte(ci);
    }

    // Ajout des 6 cartes dans la main du joueur 2
    for (int i = 0; i < 7; i++) {
        CarteClan *ci = new CarteClan(getPiocheClan()->piocherCarteClan());
        m_plateau->m_joueur2->getMain()->ajouterCarte(ci);
    }

    // Affichage des mains des joueurs
    cout << "Main du joueur 1 :" << endl;
    affichage_vecteur_carte(m_plateau->m_joueur1->getMain()->getCartes());
    cout << "Main du joueur 2 :" << endl;
    affichage_vecteur_carte(m_plateau->m_joueur2->getMain()->getCartes());
    cout << "Fin de la phase de pioche" << endl<<endl;
}

void Controleur::supprimer_carte_pose_v1(CarteClan *carte) {
    for (int i = 0; i < m_carte_non_pose.size(); i++) {
        if (m_carte_non_pose[i] == carte) {
            m_carte_non_pose.erase(m_carte_non_pose.begin() + i);
        }
    }
}
void Controleur::supprimer_carte_pose_v2(CarteClan *carte) {
    auto p = carte->getPuissance();
    auto c = carte->getCouleur();
    for (int i = 0; i < m_carte_non_pose.size(); i++) {
        if (m_carte_non_pose[i]->getPuissance() == p && m_carte_non_pose[i]->getCouleur() == c) {
            m_carte_non_pose.erase(m_carte_non_pose.begin() + i);
        }
    }
}

void Controleur::JouerTourClassique1(){
    system ("CLS");
    cout << "Voici votre main :" << endl;
    m_plateau->afficherMainJoueur(1);
    vector<Carte*> cartesMain = m_plateau->m_joueur1->getMain()->getCartes();

    cout<<"Veuillez choisir la carte que vous voulez jouer (son id) :"<<endl;
    int choix_carte, nb_tac=0,nb_clan=0,nb_total=0;
    cin>>choix_carte; clean();
    while(choix_carte>cartesMain.size() || choix_carte<0){
        cout<<"Vous n'avez pas cette carte, resaisissez une que vous avez :"<<endl;
        cin>>choix_carte;
    }
    vector<Carte*> cartes = m_plateau->m_joueur1->getMain()->getCartes();
    Carte* carte = cartes[choix_carte];
    if (auto carte_choisie = dynamic_cast<CarteClan *>(carte)) {
        for (auto carte: cartes) {
            nb_clan++;
            nb_total++;
        }
        if (nb_clan==0){
            cout << "Vous n'avez plus de cartes clans !" << endl;
            return;
        }
        if (nb_total ==0 ){
            cout << "Vous n'avez plus de cartes !" << endl;
            return; exit(0);
            }

        system ("CLS");
        cout << "Carte choisie : " << carte_choisie->getCouleur() << " " << carte_choisie->getPuissance() << endl;
        Afficher_Borne1();
        //Choix de la borne
        cout << "Veuillez choisir une borne :" << endl;
        int choix_borne;
        cin >> choix_borne;
        affichage_vecteur_carteclan(m_plateau->getBornes(choix_borne)->getCartesJ1()->getCartes());cout <<endl;
        cout << "On pose la carte piochee sur la borne "<< choix_borne << " :"<<endl;
        m_plateau->poser(*m_plateau->getBornes(choix_borne),carte_choisie);
        cout << "Borne " << choix_borne << " :" << endl;
        affichage_vecteur_carteclan(m_plateau->getBornes(choix_borne)->getCartesJ1()->getCartes());cout <<endl;
        m_plateau->getJoueur1()->getMain()->supprimerCarte(choix_carte);

    }
    CarteClan* ci = new CarteClan(getPiocheClan()->piocherCarteClan());

    m_plateau->getJoueur1()->getMain()->ajouterCarte(ci);

    cout <<"Carte piochee : "<< ci->getPuissance() <<" "<< ci->getCouleur() << endl;
    m_plateau->afficherMainJoueur(1);
    Afficher_Borne1();
    cout << "\nFIN DU TOUR" << endl;

}

// Joker tt les cartes
vector<CarteClan *> gen_vect_joker(){
    vector<CarteClan *> res;
    for (auto c : Couleurs)
        for (auto p : Puissances)
            res.push_back( new CarteClan(p, c));
    return res;

}

//Espion 7 de nimporte quel couleur
vector<CarteClan *> gen_vect_espion(){
    vector<CarteClan *> res;
    for (auto c : Couleurs)
        res.push_back( new CarteClan(Puissance::sept, c));
    return res;

}
// Porte bou
vector<CarteClan *> gen_vect_portebou(){
    vector<CarteClan *> res;
    for (auto c : Couleurs){
        res.push_back( new CarteClan(Puissance::un, c));
        res.push_back( new CarteClan(Puissance::deux, c));
        res.push_back( new CarteClan(Puissance::trois, c));
    }
    return res;

}

bool il_y_a_joker(vector<CarteClan *> v){
    for (auto c:v){
        if(auto carte =  dynamic_cast<CarteTroupeElite *>(c)){
            if (carte->getNom()=="Joker")
                return true;
        }
    }
    return false;
}

bool il_y_a_espion(vector<CarteClan *> v){
    for (auto c:v){
        if(auto carte =  dynamic_cast<CarteTroupeElite *>(c)){
            if (carte->getNom()=="Espion")
                return true;
        }
    }
    return false;
}
bool il_y_a_portebou(vector<CarteClan *> v){
    for (auto c:v){
        if(auto carte =  dynamic_cast<CarteTroupeElite *>(c)){
            if (carte->getNom()=="Porte_Bouclier")
                return true;
        }
    }
    return false;
}

int qui_gagne(Combinaison * combi1, Combinaison * combi2){
    // on regarde dabord  getForceCombi() puis getTotalPuissance() puis TODO le dernier a poser
    /*cout << "combi1 : " << combi1->getForceCombi() << " " << combi1->getTotalPuissance() << endl;
    cout << "combi2 : " << combi2->getForceCombi() << " " << combi2->getTotalPuissance() << endl;*/
    if (combi1->getForceCombi()>combi2->getForceCombi()) {
        //cout << "combi1 gagne car force combi" << endl;
        return 1;
    }
    else if (combi1->getForceCombi()<combi2->getForceCombi()) {
        //cout << "combi2 gagne car force combi" << endl;
        return 2;
    }
    else if (combi1->getTotalPuissance()>combi2->getTotalPuissance()) {
        //cout << "combi1 gagne car total puissance" << endl;
        return 1;
    }
    else if (combi1->getTotalPuissance()<combi2->getTotalPuissance()) {
        //cout << "combi2 gagne car total puissance" << endl;
        return 2;
    }
    else {
        //cout << "combi gagne car dernier a poser" << endl;
        return combi1->getPremierComplet();
    }

}

int CarteClan_egales(CarteClan* c1, CarteClan* c2){
    if (c1->getPuissance()==c2->getPuissance() && c1->getCouleur()==c2->getCouleur())
        return 1;
    else
        return 0;
}

void Controleur::jouer_partie() {
    auto *fenetre = new QWidget;
    debut_de_partie_classique();
    m_vue_plateau = new VuePlateau(fenetre);
    m_vue_plateau->setWindowState(Qt::WindowMaximized);
    m_vue_plateau->show();

    //jouer_tour();
}

void Controleur::control_piocher_clan(){
    if(m_pioche_clan->estVide()){
        cout << "La pioche est vide" << endl;
        return;
    }
    CarteClan* ci = new CarteClan(getPiocheClan()->piocherCarteClan());
    if(m_plateau->getJoueurActif()==1){
        m_plateau->getJoueur1()->getMain()->ajouterCarte(ci);
        //cout << "Joueur 1 a pioché une carte" << endl;

    }
    else{
        m_plateau->getJoueur2()->getMain()->ajouterCarte(ci);
        cout << "Joueur 2 a pioché une carte" << endl;
    }
    cout << ci->getCouleur() << " " << ci->getPuissance() << endl;
    cout << " Taille de la pioche : " << m_pioche_clan->getNbCartes() << endl;
}

void Controleur::control_piocher_tactique(){
    if(m_pioche_tactique->estVide()){
        cout << "La pioche est vide" << endl;
        return;
    }
    else {
        int n= m_pioche_tactique->quandjepiochejefaisattention();
        CarteTactique* ci;
        if (n==1){
            CarteTactique* ci = new CarteTactique(getPiocheTactique()->piocherCarteTactique());
            if(m_plateau->getJoueurActif()==1){
                m_plateau->getJoueur1()->getMain()->ajouterCarte(ci);
                cout << "Joueur 1 a pioché une carte" << endl;
            }
            else{
                m_plateau->getJoueur2()->getMain()->ajouterCarte(ci);
                cout << "Joueur 2 a pioché une carte" << endl;
            }
        }
        else {
            CarteTroupeElite* ci = new CarteTroupeElite(getPiocheTactique()->piocherCarteTroupeElite());
            if(m_plateau->getJoueurActif()==1){
                m_plateau->getJoueur1()->getMain()->ajouterCarte(ci);
                cout << "Joueur 1 a pioché une carte" << endl;
            }
            else{
                m_plateau->getJoueur2()->getMain()->ajouterCarte(ci);
                cout << "Joueur 2 a pioché une carte" << endl;
            }
        }

        cout << " Taille de la pioche : " << m_pioche_tactique->getNbCartes() << endl;
    }
}

void Controleur::lancer_tour_ia(VuePlateau* vue_plateau) {
    vector<Carte*> cartesMain = m_plateau->getJoueur2()->getMain()->getCartes();
    int id_carte = rand()%m_plateau->getJoueur2()->getMain()->getCartes().size();
    cout << "la taille de la main est" << m_plateau->getJoueur2()->getMain()->getCartes().size() << endl;
    cout << "lid de la carte est" << id_carte << endl;
    Carte* carte = cartesMain[id_carte];
    bool verif= false;
    int borne_choisie;
    if (auto carte_choisie = dynamic_cast<CarteClan *>(carte)) {
        while(!verif){
            borne_choisie = rand()%9;
            if(m_plateau->getBornes(borne_choisie)->getCartesJ2()->getCartes().size()<3){
                cout << carte_choisie->getCouleur() << " " << carte_choisie->getPuissance() << endl;
                m_plateau->poser(*m_plateau->getBornes(borne_choisie),carte_choisie);
                m_plateau->getJoueur2()->getMain()->supprimerCarte(id_carte);
                verif=true;
            }

        }

    }
    if(!m_pioche_clan->estVide()) {
        CarteClan *ci = new CarteClan(getPiocheClan()->piocherCarteClan());
        m_plateau->getJoueur2()->getMain()->ajouterCarte(ci);
    }

    for(int i=0; i<9; i++){
        if (m_plateau->getBornes(i)->getCartesJ2()->getCartes().size()==3 && m_plateau->getBornes(i)->getRevendique()==0){
            revendiquer_borne(i);
        }
    }
    vue_plateau->update_vuecartesj2();
    vue_plateau->update_vue_bornes();
    vue_plateau->update();
    lancer_suite_tour(vue_plateau);

}

void Controleur::lancer_suite_tour(VuePlateau* vue_plateau) {
    vue_plateau->set_deja_joue(false);
    if(vue_plateau->get_joueur_actif()==1){
        vue_plateau->set_joueur_actif(2);
        m_plateau->setJoueurActif(2);
    }
    else{
        vue_plateau->set_joueur_actif(1);
        m_plateau->setJoueurActif(1);
    }
    if (check_fin_partie()){
        vue_plateau->menu_fin_partie();

        cout << "Le joueur gagant est le joueur " << getGagnant()<< endl;
    } else if(m_plateau->getJoueurActif()==2 && m_plateau->getJoueur2()->getIa()){
        lancer_tour_ia(vue_plateau);
    }
}



