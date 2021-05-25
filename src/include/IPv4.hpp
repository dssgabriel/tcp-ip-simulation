/**
 * @file IPv4.hpp
 * @brief Vous trouverez ici la declaration d'une adresse IPv4, avec quelques fonctions
 *          de manipulation
 * @date 2021-05-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <bitset>
#include <iostream>

/**
 * @brief Structure d'une adresse IPv4.
 * 
 */
struct IPv4 {
    /**
     * @brief Les quatres octets de l'adresse IP.
     * 
     */
    std::bitset<8> a;
    std::bitset<8> b;
    std::bitset<8> c;
    std::bitset<8> d;

    /**
     * @brief Redefinition de l'operateur <.
     * 
     * @param ip l'adresse IP d'une autre machine.
     * @return true si `this` < ip.
     * @return false sinon.
     */
    bool operator<(const IPv4& ip) const {
        return (
              (a.to_ulong() < ip.a.to_ulong())
            & (b.to_ulong() < ip.b.to_ulong())
            & (c.to_ulong() < ip.c.to_ulong())
            & (d.to_ulong() < ip.d.to_ulong())
        );
    }

    /**
     * @brief Redefinition de l'operateur ==.
     * 
     * @param ip l'adresse IP d'une autre machine.
     * @return true si `this` == ip.
     * @return false sinon.
     */
    bool operator==(const IPv4& ip) const {
        return (
              (a.to_ulong() == ip.a.to_ulong())
            & (b.to_ulong() == ip.b.to_ulong())
            & (c.to_ulong() == ip.c.to_ulong())
            & (d.to_ulong() == ip.d.to_ulong())
        );
    }

    /**
     * @brief Redefinition de l'operateur << pour afficher l'adresse IP
     *          dans le terminal.
     * 
     * @param flux a modifier avec les informations de l'adresse IP.
     * @param ip a afficher.
     * @return std::ostream& le nouveau flux.
     */
    friend std::ostream& operator<<(
        std::ostream& flux, 
        const IPv4& ip
    ) {
        flux << ip.a.to_ulong() << "." << ip.b.to_ulong() << ".";
        flux << ip.c.to_ulong() << "." << ip.d.to_ulong();

        return flux;
    }
};

/**
 * @brief Variable globale definissant l'adresse IP zero, donc minimum, et 
 *          l'adresse maximum.
 * 
 */
extern IPv4 ipZero;
extern IPv4 ipMax;
