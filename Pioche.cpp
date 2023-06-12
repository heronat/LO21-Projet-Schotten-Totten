//
// Created by Utilisateur on 23/04/2023.
//

#include "Pioche.h"
#include "CarteException.h"

    Pioche::Pioche(const JeuClan& jeuClan) : m_cartes(new const Carte*[jeuClan.getNbCartes()]), m_nb(jeuClan.getNbCartes())
    {
        size_t i=0;
        for(auto it = jeuClan.getIterator(); !it.isDone(); it.next())
            m_cartes[i++] = &it.currentItem();


        // shuffle (un peu naif)
        for(size_t it=0; it<2*m_nb ; ++it){
            size_t a = rand() % m_nb,  b = rand() % m_nb; // on tire deux positions entre 0 et nb
            const Carte * tmp = m_cartes[a];
            m_cartes[a]=m_cartes[b];
            m_cartes[b]=tmp;
        }
    }

    Pioche::Pioche(const JeuTactique& jeuTactique) : m_cartes(new const Carte*[jeuTactique.getNbCartes()]), m_nb(jeuTactique.getNbCartes())
    {
        size_t i = 0;
        for (auto it = jeuTactique.getIterator(); !it.isDone(); it.next()) {
            m_cartes[i++] = &it.currentItem();
        }
    }

    const Carte& Pioche::piocher() {
        if(estVide()){
            throw CarteException("La pioche est vide.");
        }
        m_nb--;
        const Carte*carte = m_cartes[getNbCartes()];
        if (dynamic_cast<const CarteTactique*>(carte))
        {
            const CarteTactique* carteTactique = dynamic_cast<const CarteTactique*>(carte);
            return *new CarteTactique(*carteTactique);
        }
        else if (dynamic_cast<const CarteClan*>(carte))
        {
            const CarteClan* carteClan = dynamic_cast<const CarteClan*>(carte);
            return *new CarteClan(*carteClan);
        }

        throw CarteException("L'objet pioché n'est pas une carte");
    }

    const CarteClan& Pioche::piocherCarteClan() {
        if (estVide()) {
            throw CarteException("La pioche est vide");
        }
        m_nb--;
        const Carte*carte = m_cartes[getNbCartes()];

        const CarteClan* carteclan = dynamic_cast<const CarteClan*>(carte);
        if (!carteclan) {
            throw CarteException("La carte piochée n'est pas une carte clan.");
        }
        return *carteclan;
    }

    const CarteTactique& Pioche::piocherCarteTactique(){
        if(estVide()){
            throw CarteException("La pioche est vide.");
        }
        m_nb--;
        const Carte*carte=m_cartes[getNbCartes()];
        const CarteTactique* cartetactique = dynamic_cast<const CarteTactique*>(carte);
        if(!cartetactique){
            throw CarteException("La carte piochée n'est pas une carte tactique");
        }
        return *cartetactique;
    }
    const CarteTroupeElite& Pioche::piocherCarteTroupeElite(){
        if(estVide()){
            throw CarteException("La pioche est vide.");
        }
        m_nb--;
        const Carte*carte=m_cartes[getNbCartes()];
        const CarteTroupeElite* c = dynamic_cast<const CarteTroupeElite*>(carte);
        if(!c){
            throw CarteException("La carte piochee n'est pas une carte ELITE");
        }
        return *c;
    }


    Pioche::~Pioche()
    {
        delete [] m_cartes;
    }

    int Pioche::quandjepiochejefaisattention(){
        auto carte= m_cartes[m_nb-1];
        if (auto c1 = dynamic_cast<const CarteTactique*>(carte))
        {
            return 1;
        }
        else if (auto c2 =dynamic_cast<const CarteTroupeElite*>(carte))
        {
            return 2;
        }
        else if (auto c3 = dynamic_cast<const CarteClan*>(carte))
        {
            return 3;// surement pas utiles mais a voir

        }
        return 0;
    }
    /* utilisation des pioches
    JeuClan& jc = JeuClan::getJeuClan();
    JeuTactique& jt = JeuTactique::getJeuTactique();
    Pioche pc(jc);
    Pioche pt(jt);
    cout <<"taille pioche clan : "<<pc.getNbCartes()<<"\n";
    cout <<"taille pioche tactique : "<<pt.getNbCartes()<<"\n";
    const CarteClan& cc=dynamic_cast<const CarteClan&>(pc.piocher());
    const CarteTactique& ct=dynamic_cast<const CarteTactique&>(pt.piocher());
    cout <<"puissance carte clan : "<<cc.getPuissance()<<"\n";
    cout <<"couleur carte clan : "<<cc.getCouleur()<<"\n";
    cout<<"carte tactique : "<<ct.getNom()<<"\n";
    auto& cc2=pc.piocherCarteClan();
    auto& ct2=pt.piocherCarteTactique();
    cout <<"puissance carte clan 2 : "<<cc2.getPuissance()<<"\n";
    cout <<"couleur carte clan 2 : "<<cc2.getCouleur()<<"\n";
    cout<<"carte tactique 2 : "<<ct2.getNom()<<"\n";
    cout <<"taille pioche clan : "<<pc.getNbCartes()<<"\n";
    cout <<"taille pioche tactique : "<<pt.getNbCartes()<<"\n";*/