//
// Created by Utilisateur on 12/06/2023.
//

#ifndef LO21_SCHOTTEN_TOTTEN_VUECARTE_H
#define LO21_SCHOTTEN_TOTTEN_VUECARTE_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPushButton>
#include "CarteClan.h"

class VueCarte : public QPushButton
{
Q_OBJECT
public:
    VueCarte(const CarteClan& c, QWidget *parent = nullptr);
    explicit VueCarte(QWidget *parent = nullptr);
    // affecter une nouvelle carte à la vue
    void setCarte(CarteClan& c) { setCheckable(true); setChecked(false); carte=&c; update(); }
    // vue sans carte
    void setNoCarte() { carte=nullptr; setCheckable(false); update(); }
    const CarteClan& getCarte() const { return *carte; }
    bool cartePresente() const { return carte!=nullptr; }
private:
    const CarteClan* carte=nullptr;
signals:
    // quand la vude de carte est cliquée, elle émet un signal en transmettant son adresse
    void carteClicked(VueCarte*);
public slots:
private slots:
    void clickedEvent() { emit carteClicked(this); }
};

const char* ToString(Couleur couleur);

#endif //LO21_SCHOTTEN_TOTTEN_VUECARTE_H
