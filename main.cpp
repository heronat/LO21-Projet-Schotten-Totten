#include "VuePlateau.h"
#include "VueCarte.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QGridLayout>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QStyleFactory>
#include <string>
#include <iostream>
#include "CarteRuse.h"
#include "CarteModeCombat.h"
#include "CarteTroupeElite.h"
#include "Borne.h"
#include "Combinaison.h"
#include "CarteException.h"
#include "Controleur.h"
#include "CarteClan.h"
#include "Plateau.h"
#include "Pioche.h"
#include "Joueur.h"
#include "Main_Joueur.h"

using namespace std;

void validate_menu_1(QWidget *menu, bool version, bool Ia){
    menu->close();
    cout << Ia;
    Controleur& c = Controleur::getControleur(version, Ia);
    c.jouer_partie();
}

void launch_menu(QApplication *app){
    auto *menu = new QWidget();
    menu ->resize(500, 180);

    menu->setContentsMargins(50, 30, 50, 50);
    auto *gridLayout = new QGridLayout;

    auto *editionLabel = new QLabel("Choix de l'édition :");
    auto* editionCombo = new QComboBox();
    auto *model = new QStandardItemModel();
    auto *item1 = new QStandardItem("-- Veuillez choisir une option --");
    auto *item2 = new QStandardItem("Clan");
    auto *item3 = new QStandardItem("Tactique");

    model->appendRow(item1);
    model->appendRow(item2);
    model->appendRow(item3);

    editionCombo->setCurrentIndex(0);
    editionCombo->setMinimumWidth(200);
    editionCombo->setStyle(QStyleFactory::create("Fusion"));

    item1->setFlags(item1->flags() & ~Qt::ItemIsEnabled);

    editionCombo->setModel(model);

    gridLayout->addWidget(editionLabel, 0, 0);
    gridLayout->addWidget(editionCombo, 0, 1);

    gridLayout->addItem(new QSpacerItem(0, 15), 1, 0);

    auto *IaLabel = new QLabel("Jouer contre :");
    auto* IaCombo = new QComboBox();
    auto *modelIa = new QStandardItemModel();
    auto *item1Ia = new QStandardItem("-- Veuillez choisir une option --");
    auto *item2Ia = new QStandardItem("Joueur");
    auto *item3Ia = new QStandardItem("Ia");

    modelIa->appendRow(item1Ia);
    modelIa->appendRow(item2Ia);
    modelIa->appendRow(item3Ia);

    IaCombo->setCurrentIndex(0);
    IaCombo->setMinimumWidth(200);
    IaCombo->setStyle(QStyleFactory::create("Fusion"));

    item1Ia->setFlags(item1->flags() & ~Qt::ItemIsEnabled);

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
    gridLayout->addWidget(cancelButton, 5, 1, Qt::AlignCenter);

    QObject::connect(cancelButton, &QPushButton::clicked, app, &QApplication::quit);

    QObject::connect(validateButton, &QPushButton::clicked, [menu, editionCombo, IaCombo](){
        string edition = editionCombo->currentText().toStdString();
        string Ia = IaCombo->currentText().toStdString();
        if(Ia == "Ia"){
            cout << "test IA";
            if(edition == "Clan")
                validate_menu_1(menu, false, true);
            else if(edition == "Tactique")
                validate_menu_1(menu, true, true);
        }
        else{
            if(edition == "Clan")
                validate_menu_1(menu, false, false);
            else if(edition == "Tactique")
                validate_menu_1(menu, true, false);
        }

    });

    menu->setLayout(gridLayout);
    menu->setWindowTitle("Schotten Totten - Menu");

    menu->show();
}



int main(int argc, char * argv[]) {
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion"));
    launch_menu(&app);

    return QApplication::exec();
}
