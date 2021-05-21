/**
 * @file        DonneeReseau.cpp
 * @brief       Vous trouverez ici toutes les fonctions implementées pour la classe DonneeReseau.
 * 
 * @author      Johann RAMANANDRAITSIORY
 * @date        2021
 **/

#include "DonneeReseau.hpp"

 /**
  * @brief Constructeur de la classe DonneeReseau.
  * 
  * Le constructeur permet de créer deux fenêtres pour:
  * Exposer le graphique du contrôle de congestion + la configuration du réseau.
  * Afficher via la classe "ConfigReseau" le temps émis pour l'envoi de paquets.
  **/
DonneeReseau::DonneeReseau() : QVBoxLayout()
{
    // Creation du premier QHboxLayout
    m_F1 = new AffichageReseau();
    addLayout(m_F1);

    // Creation du deuxieme QHboxLayout
    m_F2 = new ConfigReseau();
    addLayout(m_F2);
}

 /**
  * @brief Destructeur de la classe DonneeReseau.
  * 
  * Le destructeur est vide car les classes de Qt s'autodétruisent correctement.
  * 
  **/
DonneeReseau::~DonneeReseau() {

}