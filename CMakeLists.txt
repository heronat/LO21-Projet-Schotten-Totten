cmake_minimum_required(VERSION 3.23)
project(LO21_Schotten_QT)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.5.1/mingw_64/lib/cmake")

set(SOURCE_FILES=
        main.cpp
        )

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(LO21_Schotten_QT
        main.cpp
        Borne.cpp Borne.h
        Carte.cpp Carte.h
        CarteClan.cpp CarteClan.h
        CarteException.cpp CarteException.h
        CarteModeCombat.cpp CarteModeCombat.h
        CarteRuse.cpp CarteRuse.h
        CarteTactique.cpp CarteTactique.h
        CarteTroupeElite.cpp CarteTroupeElite.h
        Combinaison.cpp Combinaison.h
        Controleur.cpp Controleur.h
        JeuClan.cpp JeuClan.h
        JeuTactique.cpp JeuTactique.h
        Joueur.cpp Joueur.h
        Main_Joueur.cpp Main_Joueur.h
        Pioche.cpp Pioche.h
        Plateau.cpp Plateau.h
        VuePlateau.cpp VuePlateau.h

        VueCarte.cpp VueCarte.h VuePioche.cpp VuePioche.h VuePlateau.cpp VuePlateau.h VueCarte.cpp VueCarte.h VuePioche.cpp VuePioche.h)
target_link_libraries(LO21_Schotten_QT
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )

if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
