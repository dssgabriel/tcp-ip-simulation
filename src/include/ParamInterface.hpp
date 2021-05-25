/**
 * @file ParamInterface.hpp
 * @brief Vous trouverez ici la declaration de la structure ParamInterface
 * @date 2021-05-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <cstdint>
#include "IPv4.hpp"

/**
 * @brief Enumeration indiquant le type de fichier a envoyer.
 * 
 */
enum TypeFichier: uint16_t {
    FTP, HTTP, SMTP, VTP
};

/**
 * @brief Structure indiquant les parametres choisis par l'utilisateur.
 * 
 */
struct ParamInterface {
    IPv4 m_Source;              //< L'adresse IP de l'ordinateur emetteur.
    IPv4 m_Destination;         //< L'adresse IP de l'ordinateur recepteur.
    uint16_t m_Ssthresh;        //< La valeur maximum de la fenetre d'emission en
                                //   'slow start'.
    uint32_t m_NbPaquet;        //< Le nombre de paquets a envoyer.
    TypeFichier m_TypeFichier;  //< Le type de fichier a envoyer.
};
