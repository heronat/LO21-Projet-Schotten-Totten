//
// Created by Utilisateur on 03/06/2023.
//

#include <QStyleFactory>
#include "VuePioche.h"
#include "Controleur.h"

VuePioche::VuePioche(Pioche* pioche, QWidget *parent) {

    if(pioche->estVide()) {
        setText(QString::fromStdString("Pioche vide"));

    }else{
        size_t n = pioche->getNbCartes();
        std::string s = "Pioche Clan (" + std::to_string(n) + ")";
        setText(QString::fromStdString(s));
    }
    setFixedSize(150, 50);
    setStyleSheet("background-color: blue; color: white;");


    barre_pioche = new QProgressBar;
    barre_pioche->setRange(0,(int)pioche->getNbCartes());
    barre_pioche->setValue((int)pioche->getNbCartes());//valeur que l'on devra mettre à jour à chaque fois qu'on pioche une carte
    barre_pioche->setFixedWidth(280);
    barre_pioche->setStyle(QStyleFactory::create("Fusion"));
}

