/**
 * 
 * @file        PaquetLSR.hpp
 * @brief       Déclaration de la classe PaquetLSR.
 * 
 * @author      Gabriel DOS SANTOS
 * @date        2021
 * 
 **/
#pragma once

#include <bitset>
#include <vector>

#include "PaquetOSPF.hpp"

class PaquetLSR: public PaquetOSPF {
    private:
        // Attributs
        uint8_t m_IdAnnonceur;
        std::vector<std::bitset<32>> m_IdLSADemandes;

    public:
        // Constructeur
        PaquetLSR(
            const uint8_t& idAnnonceur,
            const std::vector<std::bitset<32>>& idLSADemandes
        );

        // Destructeur
        ~PaquetLSR();

        // Setter & Getters
        void setEntete(const TypePaquet& type, const uint8_t& idRouteur) override;
        const TypePaquet& getType() const override;
        const uint8_t& getIdRouteur() const override;

        const uint8_t& getIdAnnonceur() const;
        std::vector<std::bitset<32>>& getIdLSADemandes();
};
