/**
 * @file MAC.hpp
 * @brief Vous trouverez ici la declaration d'une adresse MAC, avec quelques fonctions
 *          de manipulation
 * @date 2021-05-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <bitset>
#include <iostream>
#include "Commun.hpp"

/**
 * @brief Structure d'une adresse MAC.
 * 
 */
struct MAC {
    /**
     * @brief Les six octets de l'adresse MAC.
     * 
     */
    std::bitset<8> a;
    std::bitset<8> b;
    std::bitset<8> c;
    std::bitset<8> d;
    std::bitset<8> e;
    std::bitset<8> f;

    /**
     * @brief Redefinition de l'operateur ==.
     * 
     * @param mac l'adresse MAC d'une autre machine.
     * @return true si `this` == mac.
     * @return false sinon.
     */
    bool operator==(const MAC& mac) const {
        return (
              (a.to_ulong() == mac.a.to_ulong())
            & (b.to_ulong() == mac.b.to_ulong())
            & (c.to_ulong() == mac.c.to_ulong())
            & (d.to_ulong() == mac.d.to_ulong())
            & (e.to_ulong() == mac.e.to_ulong())
            & (f.to_ulong() == mac.f.to_ulong())
        );
    }

    /**
     * @brief Redefinition de l'operateur << pour afficher l'adresse MAC
     *          dans le terminal.
     * 
     * @param flux a modifier avec les informations de l'adresse MAC.
     * @param mac a afficher.
     * @return std::ostream& le nouveau flux.
     */
    friend std::ostream& operator<<(
        std::ostream& flux, 
        const MAC& mac
    ) {
        flux << std::hex << mac.a.to_ulong() << ":" << mac.b.to_ulong() << ":";
        flux << mac.c.to_ulong() << ":" << mac.d.to_ulong() << ":";
        flux << mac.e.to_ulong() << ":" << mac.f.to_ulong() << std::dec;
        
        flux << ", ";

        flux << mac.a.to_ulong() << ":" << mac.b.to_ulong() << ":";
        flux << mac.c.to_ulong() << ":" << mac.d.to_ulong() << ":";
        flux << mac.e.to_ulong() << ":" << mac.f.to_ulong();

        return flux;
    }
};

/**
 * @brief Variable globale definissant l'adresse MAC zero, donc minimum, et 
 *          l'adresse maximum.
 * 
 */
extern MAC macZero;
extern MAC macMax;