cmake_minimum_required(VERSION 3.23)
project(LO21_Schotten_totten)

set(CMAKE_CXX_STANDARD 14)

add_executable(LO21_Schotten_totten
        main.cpp Carte.cpp Carte.h CarteClan.cpp CarteClan.h CarteTactique.cpp CarteTactique.h CarteModeCombat.cpp CarteModeCombat.h CarteRuse.cpp CarteRuse.h CarteTroupeElite.cpp CarteTroupeElite.h CarteException.cpp CarteException.h Pioche.cpp Pioche.h JeuClan.cpp JeuClan.h JeuTactique.cpp JeuTactique.h Borne.cpp Borne.h Combinaison.cpp Combinaison.h Main_Joueur.cpp Main_Joueur.h Joueur.cpp Joueur.h Plateau.cpp Plateau.h Controleur.cpp Controleur.h)
