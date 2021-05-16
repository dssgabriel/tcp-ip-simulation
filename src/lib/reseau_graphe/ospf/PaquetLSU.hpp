/**
 * 
 * @file        PaquetLSU.hpp
 * @brief       Déclaration de la classe PaquetLSU.
 * 
 * @author      Gabriel DOS SANTOS
 * @date        2021
 * 
 **/
#pragma once

#include <vector>

#include "LSA.hpp"
#include "PaquetOSPF.hpp"

class PaquetLSU: public PaquetOSPF {
    private:
        // Attribut
        std::vector<LSA> m_LSADemandes;

    public:
        // Constructeur
        PaquetLSU(const std::vector<LSA>& LSADemandes);

        // Destructeur
        ~PaquetLSU();

        // Setter & Getters
        void setEntete(const TypePaquet& type, const uint8_t& idRouteur) override;
        const TypePaquet& getType() const override;
        const uint8_t& getIdRouteur() const override;

        std::vector<LSA>& getLSADemandes();
};
