//
// Created by Utilisateur on 12/06/2023.
//

#ifndef LO21_SCHOTTEN_TOTTEN_VUEPLATEAU_H
#define LO21_SCHOTTEN_TOTTEN_VUEPLATEAU_H

#include <iostream>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QGridLayout>
#include <QScrollArea>
#include <QString>
#include <QPushButton>
#include <QLCDNumber>
#include <QComboBox>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QStyleFactory>
#include <QButtonGroup>
#include <string>
#include "VueCarte.h"
#include "VuePioche.h"


class VuePlateau : public QWidget {
Q_OBJECT
public:

    explicit VuePlateau(QWidget *parent = nullptr);

    /// Update de la vue
    void update_vuecartesj1();
    void update_vuecartesj2();
    void update_vuecartesjoueur();
    void update_vue_bornes();
    void update_vue_pioche();
    void menu_fin_partie();
    /// Getters
    //QWidget* get_vue_carte() const {return fenetre_carte;}
    int get_joueur_actif() const {return j_actif;}
    bool get_deja_joue() const {return deja_joue;}
    /// Setters
    void set_joueur_actif(int i) {j_actif=i;}
    void set_deja_joue(bool b) {deja_joue=b;}

private:
    //Partie* partie_actuelle;
    unsigned int nb_joueurs;
    unsigned int joueur_affiche;
    //Labels sur la page
    QWidget* fenetre;
    QVBoxLayout* structure;
    QHBoxLayout* entete;
    QLabel* label_edj;
    QLabel* label_joueur_actuel;
    int j_actif;
    VuePioche* bouton_pioche;
    QPushButton* bouton_pioche_tactique;
    QGridLayout* body;
    VueCarte* vuecartesj1[27];
    VueCarte* vuecartesj2[27];
    QGridLayout* body2;
    QButtonGroup* groupe_bornes;
    QPushButton* bornes[9];
    QGridLayout* body3;
    QGridLayout* body4;
    QLabel* main_joueur;
    VueCarte* vuecartesmain[6];
    QPushButton* bouton_revendiquer;
    QPushButton* bouton_fin_de_tour;
    bool deja_joue;


public slots:
    void carteClique(VueCarte *vc);
    void revendiquerClique();
    void piocheClique();
    void finDeTourClique();
};


#endif //LO21_SCHOTTEN_TOTTEN_VUEPLATEAU_H
