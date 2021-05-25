/**
 * @file        MyWindow.cpp
 * @brief       Vous trouverez ici toutes les fonctions implementées pour la classe MyWindow
 *
 * @author      Raphael LIN
 * @date        2021
 **/

#include "MyWindow.hpp"

/**
 * @brief Constructeur de la classe MyWindow.
 *
 * Le constructeur permet de créer deux fenêtres pour afficher toutes les classes necessaires.
 * Il initialise aussi le Contexte.
 **/
MyWindow::MyWindow() : QWidget()
{
    //Contexte
    Contexte::GetInstance().getTemps() = 0;

    // Defintion de la fenetre de fond degrade noir vers gris, de taille initiale 500, 500, comportant un layout
    setStyleSheet("background-color: rgba(44, 47, 51, 255);");
    resize(1280, 720);
    m_Vlayout = new QVBoxLayout();

    // Creation du premier QHboxLayout
    m_F1 = new MenuEntete();
    m_Vlayout->addLayout(m_F1);

    // Creation du deuxieme QHboxLayout
    m_F2 = new FenetreReseau();
    m_Vlayout->addLayout(m_F2);

    //Attribution du QVBoxLayout comme celui de mywindow
    setLayout(m_Vlayout);

}

/**
 * @brief Destructeur de la classe MyWindow.
 *
 * Le destructeur est vide car les classes de Qt s'autodétruisent correctement.
 *
 **/
MyWindow::~MyWindow() {

}

