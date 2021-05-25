/**
 * @file Liaison.hpp
 * @brief Vous trouverez ici la declaration d'une liaison entre deux machines
 * @date 2021-05-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <stdint.h>
#include <iostream>

/**
 * @brief Structure liaison entre deux machines.
 * 
 */
struct Liaison {
    uint64_t m_Debit;       //< Debit entre les deux machines.
    uint16_t m_NumMachine1; //< Identifiant de la premiere machine.
    uint16_t m_NumMachine2; //< Identifiant de la deuxieme machine.

    /**
     * @brief Redefinition de l'operateur << pour afficher la liaison
     *          dans le terminal.
     * 
     * @param flux a modifier avec les informations de liaison.
     * @param liaison a afficher.
     * @return std::ostream& le nouveau flux.
     */
    friend std::ostream& operator<<(
        std::ostream& flux, 
        const Liaison& liaison
    ) {
        flux << liaison.m_NumMachine1 << " <- " << liaison.m_Debit;
        flux << " M -> " << liaison.m_NumMachine2;

        return flux;
    }
};