/**
 * @file    PaquetLSU.hpp
 * @brief   Declaration de la classe PaquetLSU.
 * @author  Gabriel Dos Santos
 * @date    Mai 2021
 */

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

        // Getters et setter
        virtual void setEntete(const TypePaquet& type, const uint16_t& idRouteur) override;
        virtual const TypePaquet& getType() const override;
        virtual const uint16_t& getIdRouteur() const override;

        std::vector<LSA>& getLSADemandes();
};
