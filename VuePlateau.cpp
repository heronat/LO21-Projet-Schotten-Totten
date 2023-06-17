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
    if(Controleur::getControleur(false).getTactique()){
        bouton_pioche_tactique = new VuePioche(Controleur::getControleur(false).getPiocheTactique());
        bouton_pioche_tactique->setText("Pioche : " + QString::number(Controleur::getControleur(false).getPiocheClan()->getNbCartes()));
        entete->addWidget(bouton_pioche_tactique, 0, Qt::AlignRight);
    }
    bouton_pioche = new VuePioche(Controleur::getControleur(false).getPiocheClan());
    //connect(bouton_pioche, SIGNAL(clicked()), this, SLOT(piocheClique()));
    entete->addWidget(bouton_pioche, 0, Qt::AlignRight);

    body = new QGridLayout();
    structure->addLayout(body);
    for(auto & vuecarte : vuecartesj1){
        vuecarte=new VueCarte;
    }

    for (int i = 0; i < 36; i++) {

        body->addWidget(vuecartesj1[i], i % 4, i / 4);
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
    for (int i = 0; i < 36; i++) {
        body3->addWidget(vuecartesj2[i], i % 4, i / 4);
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
    for (int i=0; i<Controleur::getControleur(false).getPlateau()->getJoueur1()->getMain()->getCartes().size() ; i++) {
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
            delete vuecartesj1[j * 4 + i];
            vuecartesj1[j * 4 + i] = new VueCarte(*carte);
            connect(vuecartesj1[j * 4 + i],SIGNAL(carteClicked(VueCarte*)),this,SLOT(carteposeClique(VueCarte*)));
            body->addWidget(vuecartesj1[j * 4 + i], (j * 4 + i) % 4, (j * 4 + i) / 4);
            i++;
        }
    }
}

void VuePlateau::update_vuecartesj2(){
    for (int j=0; j<9; j++) {
        vector<CarteClan *> vect = Controleur::getControleur(false).getPlateau()->getBornes(j)->getCartesJ2()->getCartes();
        size_t i = 0;
        for (auto &carte: vect) {
            delete vuecartesj2[j * 4 + i];
            vuecartesj2[j * 4 + i] = new VueCarte(*carte);
            connect(vuecartesj2[j * 4 + i],SIGNAL(carteClicked(VueCarte*)),this,SLOT(carteposeClique(VueCarte*)));
            body3->addWidget(vuecartesj2[j * 4 + i], (j * 4 + i) % 4, (j * 4 + i) / 4);
            i++;
        }
    }
}

void VuePlateau::update_vuecartesjoueur(){
    if (j_actif == 1) {
        vector<Carte*> vect = Controleur::getControleur(false).getPlateau()->getJoueur1()->getMain()->getCartes();
        for (int i=0; i<Controleur::getControleur(false).getPlateau()->getJoueur1()->getMain()->getCartes().size() ; i++) {
            delete vuecartesmain[i];
            vuecartesmain[i] = new VueCarte(*vect[i]);
            connect(vuecartesmain[i],SIGNAL(carteClicked(VueCarte*)),this,SLOT(carteClique(VueCarte*)));
            body4->addWidget(vuecartesmain[i], 0, i+3);
        }
        cout<<"update vuecartesjoueur"<<endl;
    }
    else {
        vector<Carte*> vect = Controleur::getControleur(false).getPlateau()->getJoueur2()->getMain()->getCartes();
        for (int i=0; i<Controleur::getControleur(false).getPlateau()->getJoueur2()->getMain()->getCartes().size() ; i++) {
            delete vuecartesmain[i];
            vuecartesmain[i] = new VueCarte(*vect[i]);
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
    if(Controleur::getControleur(false).getTactique()) {
        bouton_pioche_tactique->setText("Pioche tactique : " + QString::number(Controleur::getControleur(false).getPiocheTactique()->getNbCartes()));
    }
}

void VuePlateau::launch_menu_clan() {
    menu->close();
    Controleur::getControleur(false).control_piocher_clan();
}

void VuePlateau::launch_menu_tactique() {
    menu->close();
    Controleur::getControleur(false).control_piocher_tactique();
}

void VuePlateau::launch_menu_pioche() {
    menu = new QWidget();
    menu ->resize(500, 180);

    menu->setContentsMargins(50, 30, 50, 50);

    auto *gridLayout = new QGridLayout;

    auto *ClanButton = new QPushButton("Piocher une carte clan");
    ClanButton->setFixedWidth(200);
    ClanButton->setStyle(QStyleFactory::create("Fusion"));

    auto *TactiqueButton = new QPushButton("Piocher une carte tactique");
    TactiqueButton->setFixedWidth(200);
    TactiqueButton->setStyle(QStyleFactory::create("Fusion"));

    gridLayout->addWidget(ClanButton, 0, 0, Qt::AlignCenter);
    gridLayout->addWidget(TactiqueButton, 1, 0, Qt::AlignCenter);

    QObject::connect(ClanButton, SIGNAL(clicked()), this, SLOT(launch_menu_clan()));
    QObject::connect(TactiqueButton, SIGNAL(clicked()), this, SLOT(launch_menu_tactique()));

    menu->setLayout(gridLayout);
    menu->setWindowTitle("Menu Pioche");

    menu->show();
}

void VuePlateau::launch_menu_carte_tactique(VueCarte *vc) {
    auto *menu = new QWidget();
    menu ->resize(500, 180);
    auto carte_clan = const_cast<CarteTroupeElite *>(dynamic_cast<const CarteTroupeElite *>(&(vc->getCarte())));
    string nom = carte_clan->getNom();
    menu->setContentsMargins(50, 30, 50, 50);
    auto *gridLayout = new QGridLayout;

    auto *editionLabel = new QLabel("Choix de la valeur :");
    auto* editionCombo = new QComboBox();
    auto *model = new QStandardItemModel();
    if(nom == "Joker"){
        auto *item1 = new QStandardItem("-- Veuillez choisir une option --");
        auto *item3 = new QStandardItem("1");
        auto *item4 = new QStandardItem("2");
        auto *item5 = new QStandardItem("3");
        auto *item6 = new QStandardItem("4");
        auto *item7 = new QStandardItem("5");
        auto *item8 = new QStandardItem("6");
        auto *item9 = new QStandardItem("7");
        auto *item10 = new QStandardItem("8");
        auto *item11 = new QStandardItem("9");


        model->appendRow(item1);
        model->appendRow(item3);
        model->appendRow(item4);
        model->appendRow(item5);
        model->appendRow(item6);
        model->appendRow(item7);
        model->appendRow(item8);
        model->appendRow(item9);
        model->appendRow(item10);
        model->appendRow(item11);
        item1->setFlags(item1->flags() & ~Qt::ItemIsEnabled);
    }
    else if (nom == "Espion"){
        auto *item1 = new QStandardItem("-- Veuillez choisir une option --");
        auto *item9 = new QStandardItem("7");
        model->appendRow(item1);
        model->appendRow(item9);

        item1->setFlags(item1->flags() & ~Qt::ItemIsEnabled);
    }
    else if (nom == "Porte_Bouclier"){
        auto *item1 = new QStandardItem("-- Veuillez choisir une option --");
        auto *item3 = new QStandardItem("1");
        auto *item4 = new QStandardItem("2");
        auto *item5 = new QStandardItem("3");


        model->appendRow(item1);
        model->appendRow(item3);
        model->appendRow(item4);
        model->appendRow(item5);
        item1->setFlags(item1->flags() & ~Qt::ItemIsEnabled);
    }



    editionCombo->setCurrentIndex(0);
    editionCombo->setMinimumWidth(200);
    editionCombo->setStyle(QStyleFactory::create("Fusion"));



    editionCombo->setModel(model);

    gridLayout->addWidget(editionLabel, 0, 0);
    gridLayout->addWidget(editionCombo, 0, 1);

    gridLayout->addItem(new QSpacerItem(0, 15), 1, 0);

    auto *IaLabel = new QLabel("Choix de la couleur :");
    auto* IaCombo = new QComboBox();
    auto *modelIa = new QStandardItemModel();
    auto *item1Ia = new QStandardItem("-- Veuillez choisir une option --");
    auto *item2Ia = new QStandardItem("Jaune");
    auto *item3Ia = new QStandardItem("Vert");
    auto *item4Ia = new QStandardItem("Violet");
    auto *item5Ia = new QStandardItem("Rouge");
    auto *item6Ia = new QStandardItem("Bleu");
    auto *item7Ia = new QStandardItem("Marron");

    modelIa->appendRow(item1Ia);
    modelIa->appendRow(item2Ia);
    modelIa->appendRow(item3Ia);
    modelIa->appendRow(item4Ia);
    modelIa->appendRow(item5Ia);
    modelIa->appendRow(item6Ia);
    modelIa->appendRow(item7Ia);

    IaCombo->setCurrentIndex(0);
    IaCombo->setMinimumWidth(200);
    IaCombo->setStyle(QStyleFactory::create("Fusion"));

    item1Ia->setFlags(item1Ia->flags() & ~Qt::ItemIsEnabled);

    IaCombo->setModel(modelIa);

    gridLayout->addWidget(IaLabel, 2, 0);
    gridLayout->addWidget(IaCombo, 2, 1);

    gridLayout->addItem(new QSpacerItem(0, 15), 1, 0);

    auto *validateButton = new QPushButton("Valider");
    validateButton->setFixedWidth(200);
    validateButton->setStyle(QStyleFactory::create("Fusion"));

    auto *cancelButton = new QPushButton("Annuler");
    cancelButton->setFixedWidth(200);
    cancelButton->setStyle(QStyleFactory::create("Fusion"));

    gridLayout->addWidget(validateButton, 5, 0, Qt::AlignCenter);


    QObject::connect(validateButton, &QPushButton::clicked, [menu, editionCombo, IaCombo, vc](){
        string edition = editionCombo->currentText().toStdString();
        string Ia = IaCombo->currentText().toStdString();
        cout << "puissance: " << edition << endl;
        cout << "couleur: " << Ia << endl;
        auto carte_clan = const_cast<CarteTroupeElite *>(dynamic_cast<const CarteTroupeElite *>(&(vc->getCarte())));

        int choix_puissance = stoi(edition);
        carte_clan->setPuissance(static_cast<Puissance>(choix_puissance));
        if(Ia == "Jaune") {
            carte_clan->setCouleur(Couleur::jaune);
            cout << "test couleur jaune" << endl;
        }
        else if(Ia == "Vert") {
            carte_clan->setCouleur(Couleur::vert);
        }
        else if(Ia == "Violet") {
            carte_clan->setCouleur(Couleur::violet);
        }
        else if(Ia == "Rouge") {
            carte_clan->setCouleur(Couleur::rouge);
        }
        else if(Ia == "Bleu") {
            carte_clan->setCouleur(Couleur::bleu);
        }
        else if(Ia == "Marron") {
            carte_clan->setCouleur(Couleur::marron);
        }
        menu->close();
    });

    menu->setLayout(gridLayout);
    menu->setWindowTitle("Schotten Totten - Menu");

    menu->show();
}

void VuePlateau::carteposeClique(VueCarte *vc) {
    bool carte_adverse = false;
    if(auto carte_tactique= dynamic_cast<const CarteTroupeElite *>(&(vc->getCarte()))){
        if (j_actif == 1){
            for (auto &carte : vuecartesj2) {
                if (carte == vc){
                    QMessageBox::information(this, "Information", "Vous ne pouvez pas modifier une carte adverse");
                    carte_adverse = true;
                }
            }
            if(!carte_adverse){
                launch_menu_carte_tactique(vc);
            }
        }
        else {
            for (auto &carte : vuecartesj1) {
                if (carte == vc){
                    QMessageBox::information(this, "Information", "Vous ne pouvez pas modifier une carte adverse");
                    carte_adverse = true;
                }
            }
            if(!carte_adverse){
                launch_menu_carte_tactique(vc);
            }
        }
    }
}

void VuePlateau::carteClique(VueCarte *vc) {
    if(!deja_joue) {
        if (j_actif == 1) {
            for (int i = 0; i < 9; i++) {
                if (bornes[i]->isChecked()) {
                    if(auto carte_tactique= dynamic_cast<const CarteTactique *>(&(vc->getCarte()))){
                        if(carte_tactique->getNom()=="Colin Maillard"){
                            CarteModeCombat::jouer_ColinMaillard(Controleur::getControleur(false).getPlateau()->getBornes(i));
                            bornes[i]->setStyleSheet("background-color: limegreen; color: white;");
                            cout<< "Colin Maillard joué sur borne : "<< i << endl;
                        }
                        else if(carte_tactique->getNom()=="Combat de Boue"){
                            CarteModeCombat::jouer_CombatdeBoue(Controleur::getControleur(false).getPlateau()->getBornes(i));
                            bornes[i]->setStyleSheet("background-color: lightgreen; color: white;");
                            cout<< "Combat de boue joué sur borne : "<< i << endl;
                        }
                        string nom=carte_tactique->getNom();
                        vector<Carte *> vect = Controleur::getControleur(false).getPlateau()->getJoueur1()->getMain()->getCartes();
                        int k=0;
                        for(auto& carte:vect){
                            if(dynamic_cast<const CarteTactique *>(carte)){
                                auto* c_tact = dynamic_cast<const CarteTactique *>(carte);
                                if(c_tact->getNom()==nom){
                                    Controleur::getControleur(false).getPlateau()->getJoueur1()->getMain()->supprimerCarte(k);
                                }
                            }
                            k++;
                        }
                        launch_menu_pioche();
                        update_vuecartesj1();
                        update_vue_pioche();
                        update();

                        deja_joue = true;
                    }
                    else if (Controleur::getControleur(false).getPlateau()->getBornes(i)->getCartesJ1()->getCartes().size() <3 || (Controleur::getControleur(false).getPlateau()->getBornes(i)->getCartesJ1()->getCartes().size() <4 && Controleur::getControleur(false).getPlateau()->getBornes(i)->getCartesJ1()->getBoue())) {
                        Borne *b = Controleur::getControleur(false).getPlateau()->getBornes(i);
                        Controleur::getControleur(false).getPlateau()->poser(*b,
                                                                             const_cast<CarteClan *>(dynamic_cast<const CarteClan *>(&(vc->getCarte()))));
                        cout << "Borne " << i << " :" << endl;
                        affichage_vecteur_carteclan(
                                Controleur::getControleur(false).getPlateau()->getBornes(
                                        i)->getCartesJ1()->getCartes());

                        cout << "debug4" << endl;
                        auto &carte_int = (vc->getCarte());
                        CarteClan* c = const_cast<CarteClan *>(dynamic_cast<const CarteClan *>(&(vc->getCarte())));
                        Couleur coul = c->getCouleur();
                        cout << "Couleur de la carte choisie" << coul << endl;
                        Puissance pui = c->getPuissance();
                        cout << "Puissance de la carte choisie" << pui << endl;
                        vector<Carte *> vect = Controleur::getControleur(
                                false).getPlateau()->getJoueur1()->getMain()->getCartes();
                        //affichage_vecteur_carte(vect);
                        int j = 0;
                        cout << "debug5" << endl;
                        cout << vect.size() << endl;
                        for (auto &carte: vect) {
                            if (dynamic_cast<const CarteClan *>(carte)) {
                                const CarteClan *carteClan = dynamic_cast<const CarteClan *>(carte);
                                if (carteClan->getCouleur() == coul && carteClan->getPuissance() == pui) {
                                    cout << "debug7" << endl;
                                    cout << carteClan->getCouleur() << endl;
                                    cout << carteClan->getPuissance() << endl;
                                    cout << "i=" << j << endl;
                                    Controleur::getControleur(
                                            false).getPlateau()->getJoueur1()->getMain()->supprimerCarte(j);
                                    break;
                                }
                            }
                            j++;
                        }
                        cout << "debug6" << endl;
                        if(Controleur::getControleur(false).getTactique()){
                            launch_menu_pioche();
                        }
                        else {
                            Controleur::getControleur(false).control_piocher_clan();
                            update_vuecartesjoueur();
                        }
                        affichage_vecteur_carte(vect);
                        update_vuecartesj1();
                        update_vue_pioche();
                        update();

                        deja_joue = true;
                    } else {
                        QMessageBox::information(this, "Erreur", "La borne est pleine");
                    }
                }
            }

        } else {
            for (int i = 0; i < 9; i++) {
                if (bornes[i]->isChecked()) {
                    if(auto carte_tactique= dynamic_cast<const CarteTactique *>(&(vc->getCarte()))){
                        if(carte_tactique->getNom()=="Colin Maillard"){
                            CarteModeCombat::jouer_ColinMaillard(Controleur::getControleur(false).getPlateau()->getBornes(i));
                            bornes[i]->setStyleSheet("background-color: limegreen; color: white;");
                            cout<< "Colin Maillard joué sur borne : "<< i << endl;
                        }
                        else if(carte_tactique->getNom()=="Combat de Boue"){
                            CarteModeCombat::jouer_CombatdeBoue(Controleur::getControleur(false).getPlateau()->getBornes(i));
                            bornes[i]->setStyleSheet("background-color: lightgreen; color: white;");
                            cout<< "Combat de boue joué sur borne : "<< i << endl;
                        }
                        string nom=carte_tactique->getNom();
                        vector<Carte *> vect = Controleur::getControleur(false).getPlateau()->getJoueur2()->getMain()->getCartes();
                        int k=0;
                        for(auto& carte:vect){
                            if(dynamic_cast<const CarteTactique *>(carte)){
                                auto* c_tact = dynamic_cast<const CarteTactique *>(carte);
                                if(c_tact->getNom()==nom){
                                    Controleur::getControleur(false).getPlateau()->getJoueur2()->getMain()->supprimerCarte(k);
                                }
                            }
                            k++;
                        }
                        launch_menu_pioche();
                        update_vuecartesj2();
                        update_vue_pioche();
                        update();

                        deja_joue = true;
                    }
                    else if (Controleur::getControleur(false).getPlateau()->getBornes(i)->getCartesJ2()->getCartes().size() <3 || (Controleur::getControleur(false).getPlateau()->getBornes(i)->getCartesJ2()->getCartes().size() <4 && Controleur::getControleur(false).getPlateau()->getBornes(i)->getCartesJ2()->getBoue())) {
                        Borne *b = Controleur::getControleur(false).getPlateau()->getBornes(i);
                        Controleur::getControleur(false).getPlateau()->poser(*b,
                                                                             const_cast<CarteClan *>(dynamic_cast<const CarteClan *>(&(vc->getCarte()))));
                        cout << "Borne " << i << " :" << endl;
                        affichage_vecteur_carteclan(
                                Controleur::getControleur(false).getPlateau()->getBornes(
                                        i)->getCartesJ2()->getCartes());
                        cout << "debug4" << endl;
                        auto &carte_int = (vc->getCarte());
                        CarteClan* c = const_cast<CarteClan *>(dynamic_cast<const CarteClan *>(&(vc->getCarte())));
                        Couleur coul = c->getCouleur();
                        Puissance pui = c->getPuissance();
                        vector<Carte *> vect = Controleur::getControleur(
                                false).getPlateau()->getJoueur2()->getMain()->getCartes();
                        //affichage_vecteur_carte(vect);
                        int j = 0;
                        cout << "debug5" << endl;
                        cout << vect.size() << endl;
                        for (auto &carte: vect) {
                            if (dynamic_cast<const CarteClan *>(carte)) {
                                const CarteClan *carteClan = dynamic_cast<const CarteClan *>(carte);
                                if (carteClan->getCouleur() == coul && carteClan->getPuissance() == pui) {
                                    cout << "debug7" << endl;
                                    cout << carteClan->getCouleur() << endl;
                                    cout << carteClan->getPuissance() << endl;
                                    cout << "i=" << j << endl;
                                    Controleur::getControleur(
                                            false).getPlateau()->getJoueur2()->getMain()->supprimerCarte(j);
                                    break;
                                }
                            }
                            j++;
                        }
                        cout << "debug6" << endl;
                        if(Controleur::getControleur(false).getTactique()){
                            launch_menu_pioche();
                        }
                        else {
                            Controleur::getControleur(false).control_piocher_clan();
                            update_vuecartesjoueur();
                        }
                        affichage_vecteur_carte(vect);
                        update_vuecartesj2();
                        update_vue_pioche();
                        update();
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
                std::string msg = Controleur::getControleur(true).revendiquer_borne(i);
                QMessageBox::information(this, "Revendication", msg.c_str());
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
                std::string msg = Controleur::getControleur(true).revendiquer_borne(i);
                QMessageBox::information(this, "Revendication", msg.c_str());
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
        update_vuecartesj1();
        update_vuecartesj2();
        update_vue_bornes();
        update_vue_pioche();
        //QMessageBox::information(this, "Fin de tour", "Tour suivant !");
        label_joueur_actuel->setText(QString::fromStdString("Joueur actif : " + to_string(j_actif)));
        update();
    }
    else{
        QMessageBox::information(this, "Fin de tour", "Vous n'avez pas encore joué !");
    }
}

void VuePlateau::menu_fin_partie(){
    if (Controleur::getControleur(false).getGagnant() == 1) {
        std::string asciiArt = "           ___________  \n"
                               "         '._==_==_=_.'\n"
                               "           .-\\:      /-.\n"
                               "           | (|:.     |) |\n"
                               "            '-|:.     |-'\n"
                               "              \\::.    /\n"
                               "               '::. .'\n"
                               "                 ) (\n"
                               "               _.' '._\n"
                               "             `\"\"\"\"\"\"\"\"`\n"
                               "            \nLe joueur 1 a gagné !";

        std::cout << asciiArt << std::endl;

        QMessageBox::information(this,"Fin  de partie",asciiArt.c_str());
    }
    else {
        std::string asciiArt = "           ___________  \n"
                               "         '._==_==_=_.'\n"
                               "           .-\\:      /-.\n"
                               "           | (|:.     |) |\n"
                               "            '-|:.     |-'\n"
                               "              \\::.    /\n"
                               "               '::. .'\n"
                               "                 ) (\n"
                               "               _.' '._\n"
                               "             `\"\"\"\"\"\"\"\"`\n"
                               "            \nLe joueur 2 a gagné !";

                               std::cout << asciiArt << std::endl;
        QMessageBox::information(this, "Fin de partie", asciiArt.c_str());
    }
    for (int i=0; i<9; i++){
        cout << Controleur::getControleur(false).getPlateau()->getBornes(i)->getRevendique()<< endl;
    }
    Controleur::getControleur(false).fin_de_partie();
    this->close();

}


