//
// Created by Utilisateur on 24/04/2023.
//

#ifndef LO21_SCHOTTEN_TOTTEN_BORNE_H
#define LO21_SCHOTTEN_TOTTEN_BORNE_H
#include "Combinaison.h"

class Borne{
    int m_num;
    int m_revendique;
    Combinaison *m_cartesj1;
    Combinaison *m_cartesj2;

public :
    friend class Plateau;

    explicit Borne(int num, bool collin=false, bool boue=false):
            m_num(num), m_revendique(0){
        //printf("Borne %d cree\n", m_num);
        m_cartesj1 = new Combinaison();
        m_cartesj2 = new Combinaison();
    }
    int getNum() const {
        return m_num;
    }
    
    Combinaison* getCartesJ1() const{
        return m_cartesj1;
    }
    Combinaison* getCartesJ2() const{
        return m_cartesj2;
    }

    int getRevendique() const{
        return m_revendique;
    }

    void setNum(int num){
        m_num = num;
    }
    void setCollin(bool collin){
        m_cartesj1[0].setCollin(collin);
        m_cartesj2[0].setCollin(collin);
    }
    void setBoue(bool boue){
        m_cartesj1[0].setBoue(boue);
        m_cartesj2[0].setBoue(boue);
    }
    void setRevendique(int revendique) {
        m_revendique = revendique;
    }

    void ajouter_carte(CarteClan* carte);
};





#endif //LO21_SCHOTTEN_TOTTEN_BORNE_H
