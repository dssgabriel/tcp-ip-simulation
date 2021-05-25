/**
 * @file ElementControleCongestion.hpp
 * @brief Vous trouverez ici la declaration controle de congestion
 * @date 2021-05-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <bits/stdint-uintn.h>
#include <cstdint>

/**
 * @brief Enumeration indiquant le mode du controle de congestion.
 * 
 */
enum ModeCongestion {
    SlowStart, CongestionAvoidance, FastRetransmit, FastRecovery
};

/**
 * @brief Structure permetant de stocker un element de controle de congestion,
 *      pour l'affichage dans l'interface.
 * 
 */
struct ElementControleCongestion {
    double m_Temps;        //< Le temps a chaque changement de la fenetre d'emission.
    uint64_t m_ValeurCwnd; //< Valeur de la fentre d'emission.
    ModeCongestion m_Mode; //< Indique la partie du controle de congestion.
};
