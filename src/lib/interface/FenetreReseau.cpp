/**
 * @file        FenetreReseau.cpp
 * @brief       Vous trouverez ici toutes les fonctions implementées pour la classe FenetreReseau
 *
 * @author      Raphael LIN
 * @date        2021
 **/

#include "FenetreReseau.hpp"

/**
 * @brief Constructeur de la classe FenetreReseau.
 *
 * Le constructeur permet de créer deux fenêtres pour:
 * Afficher les boutons qui permettent de faire des choix dans le reseau.
 * Afficher la classe "DonneeReseau".
 **/
FenetreReseau::FenetreReseau() : QHBoxLayout()
{
    // Creation du premier QHboxLayout
    addLayout(&ChoixReseau::GetInstance());

    // Creation du deuxieme QHboxLayout
    m_F2 = new DonneeReseau();
    addLayout(m_F2);
}

/**
 * @brief Destructeur de la classe FenetreReseau.
 *
 * Le destructeur est vide car les classes de Qt s'autodétruisent correctement.
 *
 **/
FenetreReseau::~FenetreReseau() {

}
