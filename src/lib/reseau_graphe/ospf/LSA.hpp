/**
 * 
 * @file        LSA.cpp
 * @brief       Implémentation de la classe LSA.
 * 
 * @author      Gabriel DOS SANTOS
 * @date        2021
 * 
 **/
#pragma once

#include <bitset>
#include <cstdint>
#include <vector>

#include "../../../include/IPv4.hpp"

class LSA {
    private:
        // Attributs
        std::bitset<32> m_IdLSA;
        uint8_t m_IdRouteur;
        std::vector<IPv4> m_SousAdressesRouteur;

    public:
        // Constructeur
        LSA(const std::bitset<32>& idLSA,
            const uint8_t& idRouteur,
            const std::vector<IPv4>& sousAdressesRouteur
        );
        
        // Destructeur
        ~LSA();

        // Getters
        const std::bitset<32>& getIdLSA() const;
        const uint8_t& getIdRouteur() const;
        const std::vector<IPv4>& getSousAdressesRouteur() const;
};
