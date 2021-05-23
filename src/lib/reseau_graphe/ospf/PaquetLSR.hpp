/**
 * @file    PaquetLSR.hpp
 * @brief   Declaration de la classe PaquetLSR.
 * @author  Gabriel Dos Santos
 * @date    Mai 2021
 */

#pragma once

#include <bitset>
#include <vector>

#include "PaquetOSPF.hpp"

class PaquetLSR: public PaquetOSPF {
    private:
        // Attributs
        uint16_t m_IdEmetteur;
        std::vector<std::bitset<32>> m_IdLSADemandes;

    public:
        // Constructeur
        PaquetLSR(const uint16_t& idEmetteur,
                  const std::vector<std::bitset<32>>& idLSADemandes);

        // Destructeur
        ~PaquetLSR();

        // Getters et setter
        void setEntete(const TypePaquet& type, const uint16_t& idRouteur) override;
        const TypePaquet& getType() const override;
        const uint16_t& getIdRouteur() const override;

        const uint16_t& getIdEmetteur() const;
        std::vector<std::bitset<32>>& getIdLSADemandes();
};
