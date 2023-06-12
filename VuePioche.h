//
// Created by Utilisateur on 12/06/2023.
//

#ifndef LO21_SCHOTTEN_TOTTEN_VUEPIOCHE_H
#define LO21_SCHOTTEN_TOTTEN_VUEPIOCHE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include "Pioche.h"

class VuePioche : public QPushButton{
Q_OBJECT
public:
    VuePioche(Pioche *pioche, QWidget *parent = nullptr);
private:
    QProgressBar* barre_pioche;
};


#endif //LO21_SCHOTTEN_TOTTEN_VUEPIOCHE_H
