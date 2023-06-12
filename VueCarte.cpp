#include "Vuecarte.h"
#include <QPainter>
#include <QString>
#include <QStaticText>
#include "CarteException.h"

const char* ToStringCouleur(Couleur couleur)
{
    switch (couleur)
    {
        case Couleur::bleu:
            return "Bleu";
        case Couleur::jaune:
            return "Jaune";
        case Couleur::marron:
            return "Marron";
        case Couleur::rouge:
            return "Rouge";
        case Couleur::vert:
            return "Vert";
        case Couleur::violet:
            return "Violet";
        default:
            return "Erreur";
    }
}

const char* ToStringPuissance(Puissance puissance){
    switch (puissance)
    {
        case Puissance::zero:
            return "0";
        case Puissance::un:
            return "1";
        case Puissance::deux:
            return "2";
        case Puissance::trois:
            return "3";
        case Puissance::quatre:
            return "4";
        case Puissance::cinq:
            return "5";
        case Puissance::six:
            return "6";
        case Puissance::sept:
            return "7";
        case Puissance::huit:
            return "8";
        case Puissance::neuf:
            return "9";
        default:
            return "Erreur";
    }
}

VueCarte::VueCarte(const CarteClan& c, QWidget *parent) : QPushButton(parent),carte(&c)
{
    carte = &c;
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFixedSize(100,50);
    connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
    //setCheckable(true);
    Couleur couleur_carte = carte->getCouleur();
    const char* couleur_carte_string = ToStringCouleur(couleur_carte);
    Puissance puissance_carte = carte->getPuissance();
    const char* puissance_carte_string = ToStringPuissance(puissance_carte);
    setText(QString::fromStdString(couleur_carte_string) + QString::fromStdString(" ") + QString::fromStdString(puissance_carte_string));
    if(couleur_carte_string == "Jaune")
        setStyleSheet("background-color: gold");
    else if(couleur_carte_string == "Vert")
        setStyleSheet("background-color: limegreen");
    else if(couleur_carte_string == "Violet")
        setStyleSheet("background-color: orchid");
    else if(couleur_carte_string == "Rouge")
        setStyleSheet("background-color: crimson");
    else if(couleur_carte_string == "Bleu")
        setStyleSheet("background-color: royalblue");
    else if(couleur_carte_string == "Marron")
        setStyleSheet("background-color: chocolate");
    else
        setStyleSheet("background-color: white");

}

VueCarte::VueCarte(QWidget *parent): QPushButton(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    setFixedSize(100,50);
    connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
    //setCheckable(false);
    setText(QString::fromStdString("Carte non présente"));
}
