/**
 * @file    LSA.cpp
 * @brief   Declaration de la classe LSA.
 * @author  Gabriel Dos Santos
 * @date    Mai 2021
 */

#pragma once

#include <bitset>
#include <cstdint>
#include <vector>

#include "../../../include/IPv4.hpp"

class LSA {
    private:
        // Attributs
        std::bitset<32> m_IdLSA;
        uint16_t m_IdRouteur;
        std::vector<IPv4> m_AdrSousReseaux;

    public:
        // Constructeur
        LSA(const std::bitset<32>& idLSA,
            const uint16_t& idRouteur,
            const std::vector<IPv4>& AdrSousReseaux
        );

        // Destructeur
        ~LSA();

        // Getters
        const std::bitset<32>& getIdLSA() const;
        const uint16_t& getIdRouteur() const;
        const std::vector<IPv4>& getAdrSousReseaux() const;
};
