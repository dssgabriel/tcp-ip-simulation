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
    addLayout(&AffichageReseau::GetInstance());

    // Creation du deuxieme QHboxLayout
    addLayout(&ConfigReseau::GetInstance());
}

 /**
  * @brief Destructeur de la classe DonneeReseau.
  * 
  * Le destructeur est vide car les classes de Qt s'autodétruisent correctement.
  * 
  **/
DonneeReseau::~DonneeReseau() {

}
