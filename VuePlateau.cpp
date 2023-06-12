//
// Created by Utilisateur on 30/05/2023.
//

#include "VuePlateau.h"
#include "Controleur.h"

using namespace std;

VuePlateau::VuePlateau(QWidget *parent){
    fenetre = parent;

    structure = new QVBoxLayout();


    entete = new QHBoxLayout();
    structure->addLayout(entete);


    fenetre->setFixedSize(1500, 900);
    fenetre->setWindowTitle("Schotten Totten");
    fenetre->setStyleSheet("background-color: white;");

    label_edj = new QLabel;
    label_edj->setText("Schotten Totten ");
    label_edj->setFixedSize(300, 50);
    label_edj->setAlignment(Qt::AlignLeft);
    entete->addWidget(label_edj);

    label_joueur_actuel = new QLabel;
    j_actif = Controleur::getControleur(false).getPlateau()->getJoueurActif();
    string nom_joueur = "Joueur actuel : " + to_string(j_actif);
    label_joueur_actuel->setText(QString::fromStdString(nom_joueur));
    label_joueur_actuel->setFixedSize(300, 30);
    label_joueur_actuel->setAlignment(Qt::AlignCenter);
    label_joueur_actuel->setStyleSheet("QLabel { background-color : transparent; color : green; }");
    entete->addWidget(label_joueur_actuel, 0, Qt::AlignCenter);

    deja_joue = false;
    bouton_pioche = new VuePioche(Controleur::getControleur(false).getPiocheClan());
    //connect(bouton_pioche, SIGNAL(clicked()), this, SLOT(piocheClique()));
    entete->addWidget(bouton_pioche, 0, Qt::AlignRight);

    body = new QGridLayout();
    structure->addLayout(body);
    for(auto & vuecarte : vuecartesj1){
        vuecarte=new VueCarte;
    }

    for (int i = 0; i < 27; i++) {

        body->addWidget(vuecartesj1[i], i % 3, i / 3);
    }

    body2 = new QGridLayout();
    structure->addLayout(body2);
    groupe_bornes= new QButtonGroup(this);
    for (int i = 0; i < 9; i++) {
        bornes[i] = new QPushButton("Borne");
        bornes[i]->setFixedSize(100, 50);
        bornes[i]->setStyleSheet("background-color: forestgreen; color: white;");
        bornes[i]->setCheckable(true);
        groupe_bornes->addButton(bornes[i]);
        body2->addWidget(bornes[i], i / 9 , i % 9);
    }

    body3 = new QGridLayout();
    structure->addLayout(body3);
    for(auto & vuecarte : vuecartesj2) {
        vuecarte=new VueCarte;
    }
    for (int i = 0; i < 27; i++) {
        body3->addWidget(vuecartesj2[i], i % 3, i / 3);
    }

    body4 = new QGridLayout();
    structure->addLayout(body4);
    bouton_fin_de_tour = new QPushButton("Fin de tour");
    bouton_fin_de_tour->setFixedSize(100, 50);
    connect(bouton_fin_de_tour, SIGNAL(clicked()), this, SLOT(finDeTourClique()));

    body4->addWidget(bouton_fin_de_tour, 0, 0);
    bouton_revendiquer = new QPushButton("Revendiquer");
    bouton_revendiquer->setFixedSize(100, 50);
    connect(bouton_revendiquer, SIGNAL(clicked()), this, SLOT(revendiquerClique()));

    body4->addWidget(bouton_revendiquer, 0, 1);
    main_joueur = new QLabel("Main du Joueur :");
    body4->addWidget(main_joueur, 0, 2);
    for(auto & vuecarte : vuecartesmain) vuecarte=new VueCarte;
    vector<Carte*> vect = Controleur::getControleur(false).getPlateau()->getJoueur1()->getMain()->getCartes();
    for (int i=0; i<6 ; i++) {
        const CarteClan* carteClan = dynamic_cast<const CarteClan*>(vect[i]);
        vuecartesmain[i] = new VueCarte(*carteClan);
        connect(vuecartesmain[i],SIGNAL(carteClicked(VueCarte*)),this,SLOT(carteClique(VueCarte*)));
        body4->addWidget(vuecartesmain[i], 0, i+3);
    }
    setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowState(Qt::WindowMaximized);
    fenetre->setWindowTitle("Schotten Totten");
    setLayout(structure);
}

void VuePlateau::update_vuecartesj1(){
    for (int j=0; j<9; j++) {
        vector<CarteClan *> vect = Controleur::getControleur(false).getPlateau()->getBornes(j)->getCartesJ1()->getCartes();
        size_t i = 0;
        for (auto &carte: vect) {
            delete vuecartesj1[j * 3 + i];
            vuecartesj1[j * 3 + i] = new VueCarte(*carte);
            body->addWidget(vuecartesj1[j * 3 + i], (j * 3 + i) % 3, (j * 3 + i) / 3);
            i++;
        }
    }
}

void VuePlateau::update_vuecartesj2(){
    for (int j=0; j<9; j++) {
        vector<CarteClan *> vect = Controleur::getControleur(false).getPlateau()->getBornes(j)->getCartesJ2()->getCartes();
        size_t i = 0;
        for (auto &carte: vect) {
            delete vuecartesj2[j * 3 + i];
            vuecartesj2[j * 3 + i] = new VueCarte(*carte);
            body3->addWidget(vuecartesj2[j * 3 + i], (j * 3 + i) % 3, (j * 3 + i) / 3);
            i++;
        }
    }
}

void VuePlateau::update_vuecartesjoueur(){
    if (j_actif == 1) {
        vector<Carte*> vect = Controleur::getControleur(false).getPlateau()->getJoueur1()->getMain()->getCartes();
        for (int i=0; i<Controleur::getControleur(false).getPlateau()->getJoueur1()->getMain()->getCartes().size() ; i++) {
            const CarteClan* carteClan = dynamic_cast<const CarteClan*>(vect[i]);
            delete vuecartesmain[i];
            vuecartesmain[i] = new VueCarte(*carteClan);
            connect(vuecartesmain[i],SIGNAL(carteClicked(VueCarte*)),this,SLOT(carteClique(VueCarte*)));
            body4->addWidget(vuecartesmain[i], 0, i+3);
        }
        cout<<"update vuecartesjoueur"<<endl;
    }
    else {
        vector<Carte*> vect = Controleur::getControleur(false).getPlateau()->getJoueur2()->getMain()->getCartes();
        for (int i=0; i<Controleur::getControleur(false).getPlateau()->getJoueur2()->getMain()->getCartes().size() ; i++) {
            const CarteClan* carteClan = dynamic_cast<const CarteClan*>(vect[i]);
            delete vuecartesmain[i];
            vuecartesmain[i] = new VueCarte(*carteClan);
            connect(vuecartesmain[i],SIGNAL(carteClicked(VueCarte*)),this,SLOT(carteClique(VueCarte*)));
            body4->addWidget(vuecartesmain[i], 0, i+3);
        }
        cout<<"update vuecartesjoueur"<<endl;
    }
}

void VuePlateau::update_vue_bornes(){
    for (int i = 0; i < 9; i++) {
        int r = Controleur::getControleur(false).getPlateau()->getBornes(i)->getRevendique();
        if (r!=0) {
            bornes[i]->setText("Joueur " + QString::number(r));
            bornes[i]->setStyleSheet("background-color: orange; color: white;");
            bornes[i]->setCheckable(false);
        }
        else{
            if(Controleur::getControleur(false).getPlateau()->getBornes(i)->getCartesJ1()->getCartes().size() == 3 && Controleur::getControleur(false).getPlateau()->getBornes(i)->getCartesJ2()->getCartes().size() == 3){
                //bornes[i]->setCheckable(false);
            }
        }
    }
}

void VuePlateau::update_vue_pioche() {
    bouton_pioche->setText("Pioche : " + QString::number(Controleur::getControleur(false).getPiocheClan()->getNbCartes()));
}


void VuePlateau::carteClique(VueCarte *vc) {
    if(!deja_joue) {
        if (j_actif == 1) {
            for (int i = 0; i < 9; i++) {
                if (bornes[i]->isChecked()) {
                    if (Controleur::getControleur(false).getPlateau()->getBornes(i)->getCartesJ1()->getCartes().size() <
                        3) {
                        Borne *b = Controleur::getControleur(false).getPlateau()->getBornes(i);
                        Controleur::getControleur(false).getPlateau()->poser(*b,
                                                                             const_cast<CarteClan *>(&(vc->getCarte())));
                        cout << "Borne " << i << " :" << endl;
                        affichage_vecteur_carteclan(
                                Controleur::getControleur(false).getPlateau()->getBornes(
                                        i)->getCartesJ1()->getCartes());

                        cout << "debug4" << endl;
                        auto &c = (vc->getCarte());
                        Couleur coul = c.getCouleur();
                        Puissance pui = c.getPuissance();
                        vector<Carte *> vect = Controleur::getControleur(
                                false).getPlateau()->getJoueur1()->getMain()->getCartes();
                        //affichage_vecteur_carte(vect);
                        int i = 0;
                        cout << "debug5" << endl;
                        cout << vect.size() << endl;
                        for (auto &carte: vect) {
                            if (dynamic_cast<const CarteClan *>(carte)) {
                                const CarteClan *carteClan = dynamic_cast<const CarteClan *>(carte);
                                if (carteClan->getCouleur() == coul && carteClan->getPuissance() == pui) {
                                    cout << "debug7" << endl;
                                    cout << carteClan->getCouleur() << endl;
                                    cout << carteClan->getPuissance() << endl;
                                    cout << "i=" << i << endl;
                                    Controleur::getControleur(
                                            false).getPlateau()->getJoueur1()->getMain()->supprimerCarte(i);
                                    break;
                                }
                            }
                            i++;
                        }
                        cout << "debug6" << endl;
                        Controleur::getControleur(false).control_piocher_clan();
                        update_vuecartesj1();
                        update_vue_pioche();
                        update_vuecartesjoueur();
                        deja_joue = true;
                    } else {
                        QMessageBox::information(this, "Erreur", "La borne est pleine");
                    }
                }
            }

        } else {
            for (int i = 0; i < 9; i++) {
                if (bornes[i]->isChecked()) {
                    if (Controleur::getControleur(false).getPlateau()->getBornes(i)->getCartesJ2()->getCartes().size() <
                        3) {
                        Borne *b = Controleur::getControleur(false).getPlateau()->getBornes(i);
                        Controleur::getControleur(false).getPlateau()->poser(*b,
                                                                             const_cast<CarteClan *>(&(vc->getCarte())));
                        cout << "Borne " << i << " :" << endl;
                        affichage_vecteur_carteclan(
                                Controleur::getControleur(false).getPlateau()->getBornes(
                                        i)->getCartesJ2()->getCartes());
                        cout << "debug4" << endl;
                        auto &c = (vc->getCarte());
                        Couleur coul = c.getCouleur();
                        Puissance pui = c.getPuissance();
                        vector<Carte *> vect = Controleur::getControleur(
                                false).getPlateau()->getJoueur2()->getMain()->getCartes();
                        //affichage_vecteur_carte(vect);
                        int i = 0;
                        cout << "debug5" << endl;
                        cout << vect.size() << endl;
                        for (auto &carte: vect) {
                            if (dynamic_cast<const CarteClan *>(carte)) {
                                const CarteClan *carteClan = dynamic_cast<const CarteClan *>(carte);
                                if (carteClan->getCouleur() == coul && carteClan->getPuissance() == pui) {
                                    cout << "debug7" << endl;
                                    cout << carteClan->getCouleur() << endl;
                                    cout << carteClan->getPuissance() << endl;
                                    cout << "i=" << i << endl;
                                    Controleur::getControleur(
                                            false).getPlateau()->getJoueur2()->getMain()->supprimerCarte(i);
                                    break;
                                }
                            }
                            i++;
                        }
                        cout << "debug6" << endl;
                        Controleur::getControleur(false).control_piocher_clan();
                        update_vuecartesj2();
                        update_vue_pioche();
                        update_vuecartesjoueur();
                        deja_joue = true;
                    } else {
                        QMessageBox::information(this, "Erreur", "La borne est pleine");
                    }
                }
            }

        }
    }
    else {
        QMessageBox::information(this, "Erreur", "Vous avez déjà jouer ce tour");
    }
}

void VuePlateau::revendiquerClique() {
    for (int i=0; i<9; i++){
        if(bornes[i]->isChecked()){
            if (j_actif==1) {
                Controleur::getControleur(false).revendiquer_borne(i);
                /*switch (res) {
                    case 0:
                        QMessageBox::information(this, "Revendication", "Vous n'avez pas assez de cartes sur cette borne pour la revendiquer' !");
                        break;
                    case 1:
                        QMessageBox::information(this, "Revendication", "J2 peut encore gagner !");
                        break;
                    case 2:
                        QMessageBox::information(this, "Revendication", "J1 gagne la borne !");
                        break;
                }*/

            }

            else {
                Controleur::getControleur(false).revendiquer_borne(i);
                /*switch (res) {
                    case 0:
                        QMessageBox::information(this, "Revendication", "Vous n'avez pas assez de cartes sur cette borne pour la revendiquer' !");
                        break;
                    case 1:
                        QMessageBox::information(this, "Revendication", "J1 peut encore gagner !");
                        break;
                    case 2:
                        QMessageBox::information(this, "Revendication", "J2 gagne la borne !");
                        break;

                }*/
            }
        }
    }
    update_vue_bornes();
    update();
}

void VuePlateau::piocheClique() {

    if(j_actif==1){
        if(Controleur::getControleur(false).getPlateau()->getJoueur1()->getMain()->getCartes().size()<6){
            Controleur::getControleur(false).control_piocher_clan();
        }
        else{
            QMessageBox::information(this, "Pioche", "Vous avez déjà 6 cartes en main !");
        }
        update_vuecartesj1();
    }
    else{
        if(Controleur::getControleur(false).getPlateau()->getJoueur2()->getMain()->getCartes().size()<6){
            Controleur::getControleur(false).control_piocher_clan();
        }
        else{
            QMessageBox::information(this, "Pioche", "Vous avez déjà 6 cartes en main !");
        }
        update_vuecartesj2();
    }
}

void VuePlateau::finDeTourClique() {
    if(deja_joue){
        Controleur::getControleur(false).lancer_suite_tour(this);
        update_vuecartesjoueur();
        update_vue_bornes();
        update_vue_pioche();
        label_joueur_actuel->setText(QString::fromStdString("Joueur actif : " + to_string(j_actif)));
        update();
    }
    else{
        QMessageBox::information(this, "Fin de tour", "Vous n'avez pas encore joué !");
    }
}

void VuePlateau::menu_fin_partie(){
    if (Controleur::getControleur(false).getGagnant() == 1) {
        QMessageBox::information(this, "Fin de partie", "Le joueur 1 a gagné !");
    }
    else {
        QMessageBox::information(this, "Fin de partie", "Le joueur 2 a gagné !");
    }
    for (int i=0; i<9; i++){
        cout << Controleur::getControleur(false).getPlateau()->getBornes(i)->getRevendique()<< endl;
    }
    Controleur::getControleur(false).fin_de_partie();
    this->close();

}


