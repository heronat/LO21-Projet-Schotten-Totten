//
// Created by Utilisateur on 26/04/2023.
//

#ifndef LO21_SCHOTTEN_TOTTEN_CONTROLEUR_H
#define LO21_SCHOTTEN_TOTTEN_CONTROLEUR_H
#include "Plateau.h"
#include "Pioche.h"
#include "JeuClan.h"
#include "CarteClan.h"
#include <stdlib.h>


class Controleur {
    int m_gagnant;
    bool m_tactique; // ou const bool ?
    Pioche* m_pioche_clan;
    Pioche* m_pioche_tactique;
    Plateau* m_plateau; // ou Plateau
    JeuClan& m_jeu_clan;
    JeuTactique& m_jeu_tactique;

    vector<CarteClan *> m_carte_non_pose;

    explicit Controleur(bool m_tactique);
    ~Controleur();

    struct Handler
    {
        Controleur* controleur;
        Handler() : controleur(nullptr) {}
        ~Handler() { delete controleur; }
    };

    static Handler handler;

public:
    Controleur(const Controleur& j) = delete;
    Controleur& operator=(const Controleur& j) = delete;

    static Controleur& getControleur(bool tactique);
    static void libererControleur();

    int getGagnant() const { return m_gagnant; }
    bool getTactique() const { return m_tactique; }
    void fin_de_partie();
    /*TODO verifier si on a besoin de ces getters
    const Pioche& getPiocheClan() const { return *m_pioche_clan; }
    const Pioche& getPiocheTactique() const { return *m_pioche_tactique; }

    JeuClan getJeuClan() const { return m_jeu_clan; }
    JeuTactique getJeuTactique() const { return m_jeu_tactique; }
     */

    vector<CarteClan *> getCarteNonPose() const { return m_carte_non_pose; }
    void afficherCartesNonPose() const;

    void Afficher_Borne1();
    void Afficher_Borne2();
    Plateau* getPlateau() const { return m_plateau; }
    void setGagnant(int gagnant) { m_gagnant = gagnant; }
    void setTactique(bool tactique) { m_tactique = tactique; }
    void JouerTour1();
    void JouerTour2();
    void JouerTourIAClassique();
    void JouerTourIA();

    Pioche* getPiocheClan() const { return m_pioche_clan; }
    Pioche* getPiocheTactique() const { return m_pioche_tactique; }
    void revendiquer_borne(int num_borne);
/*    void revendiquer_borne_pleine_non_tactique(int num_borne);
    void revendiquer_borne_non_pleine_non_tactique(int num_borne );

    void revendiquer_borne_pleine_tactique(int num_borne);
    void revendiquer_borne_non_pleine_tactique(int num_borne);*/

    void debut_de_partie_classique();
    void debut_de_partie_tactique();

    void test();

    bool check_fin_partie();
    void supprimer_carte_pose_v1(CarteClan *carte);
    void supprimer_carte_pose_v2(CarteClan *carte);
    void JouerTourClassique1();

};
int qui_gagne(Combinaison * combi1, Combinaison * combi2);
int CarteClan_egales(CarteClan* c1, CarteClan* c2);
vector<CarteClan *> gen_vect_joker();
vector<CarteClan *> gen_vect_espion();
vector<CarteClan *> gen_vect_portebou();

bool il_y_a_joker(vector<CarteClan *> v);
bool il_y_a_espion(vector<CarteClan *> v);
bool il_y_a_portebou(vector<CarteClan *> v);

#endif //LO21_SCHOTTEN_TOTTEN_CONTROLEUR_H
